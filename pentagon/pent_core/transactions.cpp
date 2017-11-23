#include <stdio.h>
#include <iostream>

#include "boost/property_tree/ptree.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>
#include <pthread.h>
#include "pent_core.hpp"

void errorJson(
   std::string msg, 
   boost::property_tree::ptree &tree){
   std::stringstream s_in;
   s_in << "{\"error\":\"" + msg + "\"";
   try{
      boost::property_tree::read_json(s_in, tree);
   }catch(...){
      std::cerr << "Failed to read eosc." << std::endl;
      std::exit(1);
   }
}

void pentagon::callEosd(
   const std::string& server, 
   const std::string& port, 
   const std::string& path,
   const std::string& postjson,
   boost::property_tree::ptree &tree){

      namespace ip = boost::asio::ip;
      namespace pt = boost::property_tree;

      try{
         // asio need to have at least one io_service object:
         boost::asio::io_service io_service;

         // Resolver the server parameters into a TCP endpoint:
         ip::tcp::resolver resolver(io_service);
         ip::tcp::resolver::query query(server, port);

         // Iterator ip::tcp::resolver::iterator returns the list of endpoints:
         ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

         /* Create and connect the socket. The list of endpoints 
         may contain both IPv4 and IPv6 endpoints, so each of them has to be
         tried, until one that works. This keeps the client program 
         independent of a specific IP version. boost::asio::connect() function 
         does this automatically.
         */
         ip::tcp::socket socket(io_service);
         boost::asio::connect(socket, endpoint_iterator);

         boost::asio::streambuf request_buffer;
         std::ostream request_stream(&request_buffer);

         std::string CRNL = "\r\n";
         std::string req_string = 
            "POST " + path + " HTTP/1.0" + CRNL +
            "Host: " + server + CRNL + 
            "content-length: " + std::to_string(postjson.size()) + CRNL +
            "Accept: */*"  + CRNL +
            "Connection: close" + CRNL + CRNL +
            postjson  ;
         boost::system::error_code error;

         request_stream << req_string;
         boost::asio::write(socket, request_buffer, error);
         if( error ) {
            errorJson(error.message(), tree);
         }

         // request sent, responce expected.

         boost::asio::streambuf response_buffer;
         boost::asio::read(socket, response_buffer, boost::asio::transfer_all(), 
            error );
         if( error && error !=boost::asio::error::eof ) {
            return errorJson(error.message(), tree);
         }

         std::istream response_stream(&response_buffer);
         std::string http_version;
         response_stream >> http_version;
         unsigned int status_code;
         response_stream >> status_code;
         std::string status_message;
         getline(response_stream, status_message);
         if (status_code != 200 ) {
            errorJson(status_message, tree);
         }

         std::string message(boost::asio::buffer_cast<const char*>(response_buffer.data()));
         std::string mark = CRNL + CRNL; // header end mark
         std::size_t found = message.find(mark);
         message = message.substr(found + mark.length(), message.length());
         
         std::stringstream s_in;
         s_in << message;
         try{
            boost::property_tree::read_json(s_in, tree);
         }catch(...){
            std::cerr << "Failed to read eosc." << std::endl;
            std::exit(1);
         }
      }catch (std::exception& e){
         return errorJson(e.what(), tree);
      }
   
      return errorJson("impossible!", tree);
   }
