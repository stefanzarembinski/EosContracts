#include <stdio.h>
#include <iostream>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <boost/asio.hpp>
//#include <boost/log/trivial.hpp>
#include <pthread.h>

#include "transactions.hpp"

using namespace std;

string callEsod( 
   const string& server, 
   const string& port, 
   const string& path,
   const string& postjson){
         
   return "";
}

string errorJson (string message){
   //stringstream re;
   //re << boost::format::basic_format("{\"error\":\"%1%\"}") % message;
   //return re.str();
   return "";
}

string callEosd1(
   const string& server, 
   const string& port, 
   const string& path,
   const string& postjson){
      using boost::asio::ip::tcp;

      try{
         // asio need to have at least one io_service object:
         boost::asio::io_service io_service;

         // Resolver the server parameters into a TCP endpoint:
         tcp::resolver resolver(io_service);
         tcp::resolver::query query(server, port);

         // Iterator ip::tcp::resolver::iterator returns the list of endpoints:
         tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

         /* Create and connect the socket. The list of endpoints 
         may contain both IPv4 and IPv6 endpoints, so each of them has to be
         tried, until one that works. This keeps the client program 
         independent of a specific IP version. boost::asio::connect() function 
         does this automatically.
         */
         tcp::socket socket(io_service);
         boost::asio::connect(socket, endpoint_iterator);

         boost::asio::streambuf request;
         ostream request_stream(&request);
         request_stream << "POST " << path << " HTTP/1.0\r\n";
         request_stream << "Host: " << server << "\r\n";
         request_stream << "content-length: " << postjson.size() << "\r\n";
         request_stream << "Accept: */*\r\n";
         request_stream << "Connection: close\r\n\r\n";
         request_stream << postjson;
         boost::asio::write(socket, request);

         boost::asio::streambuf response;
         boost::asio::read_until(socket, response, "\r\n");
         
         istream response_stream(&response);
         string http_version;
         response_stream >> http_version;
         unsigned int status_code;
         response_stream >> status_code;
         string status_message;
         getline(response_stream, status_message);
         if (status_code != 200 ) {
            return errorJson(status_message);
         }
         
         // Skip the response headers: they are terminated by a blank line.
         boost::asio::read_until(socket, response, "\r\n\r\n");

         stringstream re;
         // Write whatever content we already have to output.
         if (response.size() > 0){
               //cout << &response;
               re << &response;
         }
         // Read until EOF, writing data to output as we go.
         boost::system::error_code error;
         while (boost::asio::read(socket, response,
               boost::asio::transfer_at_least(1), error))
            re << &response;

         if (error != boost::asio::error::eof){
            throw boost::system::system_error(error);
            cout << re.str() <<"\n";
         }
         
         return re.str();

      }catch (std::exception& e){
         std::cerr << e.what() << std::endl;
      }
   
      return errorJson("impossible!");
   }

string callEsodEOS( 
   const string& server, 
   const string& port, 
   const string& path,
   const string& postjson){
      try 
      {
         boost::asio::io_service io_service;

         // Get a list of endpoints corresponding to the server name.
         boost::asio::ip::tcp::resolver resolver(io_service);
         boost::asio::ip::tcp::resolver::query query(server, port );
         boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
         boost::asio::ip::tcp::resolver::iterator end;
         
         while( endpoint_iterator != end ) {
            /* 
            Try each endpoint until we successfully establish a connection.
            boost::asio::ip::tcp::socket is an example of I/O object
            The socket object forwards the request to the io_service. 
            */
            boost::asio::ip::tcp::socket socket(io_service);

            try {
               boost::asio::connect(socket, endpoint_iterator);
               endpoint_iterator = end;
            } catch( exception& e ) {
               throw;
            }

            // Form the request. We specify the "Connection: close" header so that the
            // server will close the socket after transmitting the response. This will
            // allow us to treat all data up until the EOF as the content.
            boost::asio::streambuf request;
            ostream request_stream(&request);
            request_stream << "POST " << path << " HTTP/1.0\r\n";
            request_stream << "Host: " << server << "\r\n";
            request_stream << "content-length: " << postjson.size() << "\r\n";
            request_stream << "Accept: */*\r\n";
            request_stream << "Connection: close\r\n\r\n";
            request_stream << postjson;

            // Send the request.
            boost::asio::write(socket, request);

            // Read the response status line. The response streambuf will automatically
            // grow to accommodate the entire line. The growth may be limited by passing
            // a maximum size to the streambuf constructor.
            boost::asio::streambuf response;
            boost::asio::read_until(socket, response, "\r\n");

            // Check that response is OK.
            istream response_stream(&response);
            string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            string status_message;
            getline(response_stream, status_message);
            
            // Read the response headers, which are terminated by a blank line.
            boost::asio::read_until(socket, response, "\r\n\r\n");
            
            stringstream re;
            // Write whatever content we already have to output.
            if (response.size() > 0){
                  //cout << &response;
                  re << &response;
            }
            // Read until EOF, writing data to output as we go.
            boost::system::error_code error;
            while (boost::asio::read(socket, response,
                  boost::asio::transfer_at_least(1), error))
               re << &response;

            if (error != boost::asio::error::eof){
               throw boost::system::system_error(error);
               cout << re.str() <<"\n";
            }
            
            if( status_code == 200 ) {
               return re.str();
            } else {
               return "ERROR";
            }
         }         
      } catch (exception& e) {
         cerr << e.what() << '\n';
         throw;
      }
      return "";
   }
