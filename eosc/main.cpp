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

void test1 () {
  tokenika::eosc::get_info get_info;
  cout << "is error set = " << get_info.is_error() << endl;
  cout << get_info.to_string_post() << endl;
  cout << get_info.to_string_rcv() << endl;
  if (get_info.is_error())
  {
    cout << get_info.to_string_rcv() << endl;
  }else
  {
    cout << get_info.get<int>("last_irreversible_block_num");
    cout << get_info.get<string>("head_block_id") << endl;
    cout << get_info.get<string>("head_block_time") << endl;
    boost::posix_time::ptime time = get_info.get<boost::posix_time::ptime>("head_block_time");
    cout << time << endl;

    boost::posix_time::ptime t1 = time + boost::posix_time::seconds(900);
    cout << (boost::posix_time::to_iso_extended_string)(t1) << endl;
    cout << get_info.get<string>("last_irreversible_block_num") << endl;
    {
      tokenika::eosc::get_block
          get_block(get_info.get<int>("last_irreversible_block_num"));
      if (get_block.is_error())
      {
        cout << get_block.to_string_rcv() << endl;
      } 
      else
      {
        cout << get_block.to_string_rcv() << endl;
      }
    }
    {
      tokenika::eosc::get_block
          get_block(get_info.get<string>("head_block_id"));
      if (get_block.is_error())
      {
        cout << get_block.to_string_rcv() << endl;
      } 
      else
      {
        cout << get_block.to_string_rcv() << endl;
      }
    }
  }
}

void test2(){
  vector<string> 

  args = {"tokenika::eosc::command_options", "--xxx"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_info_options>(args);

  args = {"tokenika::eosc::command_options", "--help", "--raw"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_info_options>(args);

  args = {"tokenika::eosc::command_options", "--example"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_info_options>(args);

  args = {"tokenika::eosc::command_options", "--block_num", "25"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_info_options>(args);  

  args = {"tokenika::eosc::command_options", "--help", "--raw"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_block_options>(args);

  args = {"tokenika::eosc::command_options", "--example"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_block_options>(args);

  args = {"tokenika::eosc::command_options", "--block_num", "25"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_block_options>(args); 

  args = {"tokenika::eosc::command_options", "--json", 
    R"EOF({"block_num_or_id":"25"})EOF"};
  cout << boost::algorithm::join(args, ", ") << endl;
  tokenika::eosc::set_options<tokenika::eosc::get_block_options>(args); 
}

#define IF_ELSE(name) \
if(command_name == #name) \
{tokenika::eosc::name##_options(argc, argv).go();} \
else

int main(int argc, const char *argv[])
{
  string command_name;
  if(argc > 1){
    command_name = argv[1];
    command_name +="_";
    argv++;
    argc--;
    if(argc > 1){
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


