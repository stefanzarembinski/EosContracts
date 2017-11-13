#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <boost/asio.hpp>
#include "boost/format.hpp"
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/program_options.hpp>

#include <pthread.h>

using namespace std;
using boost::format;

string errorJson (string message){
   stringstream re;
   re << format("{\"error\":\"%1%\"}") % message;
   return re.str();
}

string callEosd(
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

         boost::asio::streambuf request_buffer;
         ostream request_stream(&request_buffer);

         string CRNL = "\r\n";
         string req_string = 
            "POST " + path + " HTTP/1.0" + CRNL +
            "Host: " + server + CRNL + 
            "content-length: " + std::to_string(postjson.size()) + CRNL +
            "Accept: */*"  + CRNL +
            "Connection: close" + CRNL + CRNL +
            postjson
         ;
         boost::system::error_code error;

         BOOST_LOG_TRIVIAL(debug) << CRNL << "request: " << CRNL << CRNL
            << req_string;

         request_stream << req_string;
         boost::asio::write(socket, request_buffer, error);
         if( error ) {
            return errorJson(error.message());
         }

         // request sent, responce expected.

         boost::asio::streambuf response_buffer;
         boost::asio::read(socket, response_buffer, boost::asio::transfer_all(), 
            error );
         if( error && error !=boost::asio::error::eof ) {
            return errorJson(error.message());
         }

         istream response_stream(&response_buffer);
         string http_version;
         response_stream >> http_version;
         unsigned int status_code;
         response_stream >> status_code;
         string status_message;
         getline(response_stream, status_message);
         if (status_code != 200 ) {
            return errorJson(status_message);
         }

         string message(boost::asio::buffer_cast<const char*>(response_buffer.data()));
         BOOST_LOG_TRIVIAL(debug) << CRNL << "message: " << CRNL << CRNL
            << message;
         string mark = CRNL + CRNL; // header end mark
         std::size_t found = message.find(mark);
         message = message.substr(found + mark.length(), message.length());
         BOOST_LOG_TRIVIAL(debug) << CRNL << "message: " << CRNL << CRNL
            << message;
         return message;

      }catch (std::exception& e){
         return errorJson(e.what());
      }
   
      return errorJson("impossible!");
   }

void tryJson () {
   namespace pt = boost::property_tree;

      const char* launchJson = R"foo(
{
   "version": "0.2.0",
   "configurations": [
      { << CRNL
         "name": "(gdb) Launch",
         "type": "cppdbg",
         "request": "launch",
         "program": "/mnt/hgfs/Workspaces/EOS/eoscBash/Contracts/hello2/build/ContractHello",
         "args": [],
         "stopAtEntry": false,
         "cwd": "${workspaceRoot}",
         "environment": [],boost::log::std::cout << "send failed: " << error.message() << std::endl;
         "externalConsole": true,
         "MIMode": "gdb",
         "setupCommands": [boost::log:: << CRNL
            {
               "description": "Enable pretty-printing for gdb",
               "text": "-enable-pretty-printing",
               "ignoreFailures": true
            }
         ]
      }
   ]
}
)foo";

   std::cout << "Original json string:" << std::endl << std::endl;  
   std::cout << launchJson << std::endl;  
   
   std::stringstream inputString;
   inputString << launchJson;

   pt::ptree json;
   pt::read_json(inputString, json);
   json.put("version", "1.1.1");
 
   std::stringstream outputString;
   pt::write_json(outputString, json);

   std::cout << std::endl << "Processed json string:" << std::endl << std::endl;
   std::cout << outputString.str() << std::endl;
   
   //pt::write_json(std::cout, json);
}

struct info{
   int head_block_num;
   int last_irreversible_block_num;
   string head_block_id;
   string head_block_time;
   string head_block_producer;
   string recent_slots;
   long participation_rate;
   void load(const std::string &filename);
   void save(const std::string &filename);
};




int main (int argc, char *argv[]) {

// logging settings
   boost::log::trivial::severity_level logSeverity;
   boost::program_options::options_description loggingSettings
   ("Logging settings");
   loggingSettings.add_options()
   ("LogSeverity", boost::program_options::value<boost::log::trivial::severity_level>(&logSeverity)
   ->required(),
   "log level to output");

   std::ifstream conf_file("./default.conf");
   if (!conf_file){
      cerr << "Cannot find ./default.conf!!";
      return 1;
   }

   boost::program_options::variables_map variables_map;
   boost::program_options::store(boost::program_options::parse_config_file(conf_file, loggingSettings), variables_map);
   boost::program_options::notify(variables_map);

   boost::log::core::get()->set_filter(
   boost::log::trivial::severity >= logSeverity);
   BOOST_LOG_TRIVIAL(info) << "severity " << logSeverity;


   //tryJson();

   const string server = "localhost";
   const string port = "8888";
   const string path = "/v1/chain/get_info";
   const string postjson = "";

   //printf("", server, port, );
   string json = callEosd(server, port, path, postjson);
   cout <<json << "\n";

   return 0;
}