#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/algorithm/string/join.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#include "eosc_commands/eosc_get_commands.hpp"

using namespace std;

void test(){
  vector<string> 

  args = {"tokenika::eosc::command_options", "--xxx"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_infoOptions>(args);

  args = {"tokenika::eosc::command_options", "--help", "--raw"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_infoOptions>(args);

  args = {"tokenika::eosc::command_options", "--example"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_infoOptions>(args);

  args = {"tokenika::eosc::command_options", "--block_num", "25"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_infoOptions>(args);  

  args = {"tokenika::eosc::command_options", "--help", "--raw"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_blockOptions>(args);

  args = {"tokenika::eosc::command_options", "--example"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_blockOptions>(args);

  args = {"tokenika::eosc::command_options", "--block_num", "25"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_blockOptions>(args); 

  args = {"tokenika::eosc::command_options", "--json", 
    R"EOF({"block_num_or_id":"25"})EOF"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_blockOptions>(args); 
}

#define IF_ELSE(name) \
if(command_name == #name) \
{tokenika::eosc::name##Options(argc, argv).go();} \
else

int main(int argc, const char *argv[])
{
  string command_name;
  if(argc > 1){
    command_name = argv[1];
    if(command_name == "test"){
      test();
      return 0;
    }
    argv++;
    argc--;
    if(argc > 1){
      command_name +="_";
      command_name += argv[1];
      argv++;
      argc--;
      IF_ELSE(get_info)
      IF_ELSE(get_block)
      {
        cerr << "unknown command!";
      }
    }
  }
  return 0;
}


