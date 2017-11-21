#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "pentagon1/pentagon1.hpp"

void tryJson () {
   namespace pt = boost::property_tree;
   
   const char* launchJson = R"EoF(
{
   "version": "0.2.0",
   "configurations": [
      {
         "name": "(gdb) Launch",
         "type": "cppdbg",
         "request": "launch",
         "program": "/mnt/hgfs/Workspaces/EOS/eoscBash/Contracts/hello2/build/ContractHello",
         "args": [],
         "stopAtEntry": false,
         "cwd": "${workspaceRoot}",
         "environment": [],
         "externalConsole": true,
         "MIMode": "gdb",
         "setupCommands": [
            {
               "description": "Enable pretty-printing for gdb",
               "text": "-enable-pretty-printing",
               "ignoreFailures": true
            }
         ]
      }
   ]
}
)EoF";

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

int main (int argc, char *argv[]) {

   tryJson();

   using namespace std;

   const string server = "localhost";
   const string port = "8888";
   const string path = "/v1/chain/get_info";
   const string postjson = "";

   pentagon::callEosd(server, port, path, postjson);
   //callEsod(server, port, path, postjson);

   return 0;
}