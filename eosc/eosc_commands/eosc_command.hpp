#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/program_options.hpp>

#define ERROR "error" // Error json key

namespace tokenika::eosc{

  extern boost::posix_time::ptime strtotime(const std::string str);

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
    
  template<typename Type> 
  Type get1(boost::property_tree::ptree json,
    const boost::property_tree::ptree::path_type & path);

  class eosc_command {
      std::string path;
      boost::property_tree::ptree rcv_json;
      bool is_error_set = false;
      bool is_raw;

    protected:
      boost::property_tree::ptree post_json;

    public:
      eosc_command(
          std::string path, 
          boost::property_tree::ptree post_json,
          bool is_raw = false) 
            : path(path), post_json(post_json), is_raw(is_raw) {}

      void call_eosd(){
        if(!eosc_command_json(path, post_json, rcv_json)){
            is_error_set = true;
        }
      }

      bool is_error() const {
        return is_error_set;
      }

      boost::property_tree::ptree get_resp_json() const {
        return rcv_json;
      }

      std::string to_string_post() const;
      std::string to_string_rcv() const;
      template<typename Type> 
      Type get(const boost::property_tree::ptree::path_type & path) const{
        return get1<Type>(rcv_json, path);
    }  
  };

}