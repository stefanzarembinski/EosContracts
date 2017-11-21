#include <stdlib.h>
#include <string>

#pragma once

namespace pentagon{
   
using namespace std;

   string eos_name(
      const unsigned long long ull);

   unsigned long long eos_name(
      const char* str);

   extern string callEosd(
      const string& server, 
      const string& port,
      const string& path,
      const string& postjson);

   extern string callEosd1( 
      const string& server, 
      const string& port, 
      const string& path,
      const string& postjson);

}