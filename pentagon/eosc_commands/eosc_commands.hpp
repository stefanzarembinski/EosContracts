#ifndef EOS_COMMANDS_HPP___
#define EOS_COMMANDS_HPP___

#include <stdlib.h>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#define ERROR "error" // Error json key

namespace pentagon{

  extern boost::posix_time::ptime strtotime(const std::string str);  
  
  template<typename Type> Type get1(boost::property_tree::ptree json,
    const boost::property_tree::ptree::path_type & path);

  template<> boost::posix_time::ptime get1(boost::property_tree::ptree json,
      const boost::property_tree::ptree::path_type & path);

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

#endif //EOS_COMMANDS_HPP___