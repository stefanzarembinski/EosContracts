#include <stdio.h>
#include <iostream>
#include <cstdarg>

#include "boost/property_tree/json_parser.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

#include <pthread.h>

#include "eosc_command.hpp"
#include <eosc_config.h>

namespace tokenika::eosc{

  void output(const char* label, const char* format, ...){
    std::printf("## %20s: ", label);

    std::string f(format);
    f += "\n";

    va_list argptr;    
    va_start(argptr, format);
    std::vprintf(f.c_str(), argptr);
    va_end(argptr);
  }

  template<typename Type> Type get1(boost::property_tree::ptree json,
    const boost::property_tree::ptree::path_type & path){
    return json.get<Type>(path);
  }

  template<> boost::posix_time::ptime get1(boost::property_tree::ptree json,
      const boost::property_tree::ptree::path_type & path){
      return strtotime(json.get<std::string>(path));
  }

  struct init_get1{
    /*
    Template function has to be used, in order to force compiler
    to build specific forms needed elsewhere in the program and 
    in the library.
    */
    std::string strVal;
    int intVal;
    float floatVal;
    boost::posix_time::ptime ptime;

    init_get1(){
      try{
        boost::property_tree::ptree json;
        boost::property_tree::ptree::path_type path;

        strVal = get1<std::string>(json, path);
        intVal = get1<int>(json, path);
        floatVal = get1<float>(json, path);
        ptime = get1<boost::posix_time::ptime>(json, path);
      } catch(...){}
    }
  };
  init_get1 init;

  boost::posix_time::ptime strtotime(const std::string str){
    std::string temp = boost::replace_all_copy(str, "-", "");
    temp = boost::replace_all_copy(temp, ":", "");
    boost::posix_time::ptime t((boost::posix_time::from_iso_string)(temp));
    return t;
  }

  boost::property_tree::ptree string_to_ptree(std::string json){
    boost::property_tree::ptree ptree;
    try {
      std::stringstream ss; 
      ss << json;
      boost::property_tree::read_json(ss, ptree);
    } catch(...){
      std::cerr << "argument json is missformatted." << std::endl;
    }
    return ptree;
  }  

  bool eosc_command_json(
    std::string path, 
    boost::property_tree::ptree &post_json, 
    boost::property_tree::ptree &rcv_json)
    {
        
    boost::property_tree::ptree config;
    boost::property_tree::read_json(CONFIG_JSON, config);

    callEosd(
        config.get("eosc.server", "localhost"), 
        config.get("eosc.port", "8888"), 
        path, 
        post_json, 
        rcv_json);
    try{
        rcv_json.get<std::string>(ERROR);
        return false;
    } catch(...){ 
        return true;
    }  
  }

  void callEosd(
    std::string server, 
    std::string port, 
    std::string path,
    boost::property_tree::ptree &post_json,
    boost::property_tree::ptree &rcv_json)
    {

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

      std::stringstream ss;
      boost::property_tree::json_parser::
        write_json(ss, post_json, false);
      std::string post_msg = ss.str();
      boost::trim(post_msg);
      
      std::string CRNL = "\r\n";
      std::string req_string = 
        "POST " + path + " HTTP/1.0" + CRNL +
        "Host: " + server + CRNL + 
        "content-length: " + std::to_string(post_msg.size()) + CRNL +
        "Accept: */*"  + CRNL +
        "Connection: close" + CRNL + CRNL +
        post_msg;
      boost::system::error_code error;

      request_stream << req_string;
      boost::asio::write(socket, request_buffer, error);
      if( error ) {
        rcv_json.put(ERROR, error.message());
        return;
      }

      // request sent, responce expected.

      boost::asio::streambuf response_buffer;
      boost::asio::read(socket, response_buffer, boost::asio::transfer_all(), 
        error );
      if( error && error !=boost::asio::error::eof ) {
        rcv_json.put(ERROR, error.message());
        return;
      }

      std::istream response_stream(&response_buffer);
      std::string http_version;
      response_stream >> http_version;
      unsigned int status_code;
      response_stream >> status_code;
      std::string status_message;

      getline(response_stream, status_message);
      if (status_code != 200 ) {
        rcv_json.put(ERROR, status_message);
        return;
      }

      std::string message(boost::asio::buffer_cast<const char*>(response_buffer.data()));
      std::string mark = CRNL + CRNL; // header end mark
      std::size_t found = message.find(mark);
      message = message.substr(found + mark.length(), message.length());
      
      std::stringstream s_in;
      s_in << message;
      try{
        boost::property_tree::read_json(s_in, rcv_json);
      }catch(...){
        rcv_json.put(ERROR, "Failed to read eosc.");
        return;
      }
        
    }catch (std::exception& e){
        rcv_json.put(ERROR, e.what());
        return;
    }
  }

/***************************************************************************
  Definitions for class eosc_command.
****************************************************************************/
    std::string eosc_command::to_string_post() const {
      std::stringstream ss;
      try{
      boost::property_tree::json_parser::
        write_json(ss, post_json, !is_raw);
      }catch(...){
        std::stringstream msg;
        std::exception_ptr p = std::current_exception();
        msg <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        return msg.str();
      }
      return ss.str();
    }

    std::string eosc_command::to_string_rcv() const {
      std::stringstream ss;
      try{
        boost::property_tree::json_parser::
          write_json(ss, rcv_json, !is_raw);
      } catch(...){
        std::stringstream msg;
        std::exception_ptr p = std::current_exception();
        msg <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        return msg.str();
      }
      return ss.str();
    }


/******************************************************************************
  Definitions for class 'command_options'
******************************************************************************/

  void command_options::go(){
    try{
      bool is_raw = false;
      bool is_print = false;

      boost::program_options::options_description desc{"Options"};
      boost::program_options::options_description common("");
      common_options(common);
      desc.add(options()).add(common);

      boost::program_options::positional_options_description pos_desc;
      set_pos_desc(pos_desc);

      boost::program_options::command_line_parser parser{argc, argv};
      parser.options(desc).positional(pos_desc).allow_unregistered();
      boost::program_options::parsed_options parsed_options = parser.run();

      boost::program_options::variables_map vm;
      store(parsed_options, vm);
      notify(vm);
    
      bool is_arg = set_json(vm) || vm.count("json");
      if(vm.count("json")){
        post_json = string_to_ptree(json);
      }
      is_raw = vm.count("raw");

      if (vm.count("help")){
        std::cout << get_usage() << std::endl;
        std::cout << desc << std::endl;
      } else if(vm.count("example")){
          get_example();
      } else if(is_arg){
        eosc_command command = get_command(is_raw);
        if(vm.count("received")){
          std::cout << command.to_string_rcv() << std::endl;
        } else{
          get_output(command);
        }
      } else if (vm.count("unreg")){
        std::cout << get_usage() << std::endl;
        std::cout << desc << std::endl;
      }
    } catch (const boost::program_options::error &ex){
      std::cerr << ex.what() << std::endl;
    }
  } 
}    
