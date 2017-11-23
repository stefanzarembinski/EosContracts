#include <stdlib.h>
#include <string>
#include <boost/property_tree/ptree.hpp>

#pragma once

namespace pentagon{

   extern std::string eos_name(
      const unsigned long long ull);

   extern unsigned long long eos_name(
      const char* str);

   extern void callEosd(
      const std::string& server, 
      const std::string& port, 
      const std::string& path,
      const std::string& postjson,
      boost::property_tree::ptree &tree);
}