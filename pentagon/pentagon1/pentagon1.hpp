#include <stdlib.h>
#include <string>

#pragma once

namespace pentagon{
   
using namespace std;

   extern "C" {
      void eos_name2string(
         const unsigned long long ull, 
         const char* out);
      unsigned long long eos_name2uint(
         const char* name);
   }

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