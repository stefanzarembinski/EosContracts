#include <stdlib.h>
#include <string>

#pragma once

using namespace std;

extern string callEsod(
   const string& server, 
   const string& port,
   const string& path,
   const string& postjson);

extern string callEsod1( 
   const string& server, 
   const string& port, 
   const string& path,
   const string& postjson);