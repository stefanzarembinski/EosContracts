#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#define ERROR "error" // Error json key

namespace pentagon{

  extern boost::posix_time::ptime strtotime(const std::string str);

  template<typename Type> 
  Type get1(boost::property_tree::ptree json,
    const boost::property_tree::ptree::path_type & path);

  class eosc_command {
    protected:
      boost::property_tree::ptree post_json;
      boost::property_tree::ptree rcv_json;
      bool is_error_set = false;

    public:
      static constexpr const char* common_help =
R"EOF(
  -h,--help ... Print this help message and exit.
  --default ... Use default args.
  --post ... Print post json.
  --json ... Print received json.
  --pretty
)EOF";      

      bool is_error() const {
        return is_error_set;
      }

      boost::property_tree::ptree get_resp_json() const {
        return rcv_json;
      }

      std::string to_string_post(bool pretty = true) const;
      std::string to_string_rcv(bool pretty = true) const;
      template<typename Type> 
      Type get(const boost::property_tree::ptree::path_type & path) const{
        return get1<Type>(rcv_json, path);
    }  
  };

  extern bool eosc_command_json(
    std::string path, 
    boost::property_tree::ptree &post_json, 
    boost::property_tree::ptree &rcv_json);

  extern void callEosd(
    std::string server, 
    std::string port, 
    std::string path,
    boost::property_tree::ptree &post_json,
    boost::property_tree::ptree &rcv_json);
}
