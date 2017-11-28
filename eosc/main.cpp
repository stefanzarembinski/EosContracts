#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "eosc_commands/eosc_get_commands.hpp"

int main (int argc, char *argv[]) {

  using namespace std;

  cout << pentagon::get_info::help << pentagon::eosc_command::common_help << endl;
  pentagon::get_info get_info;
  cout << "is error set = " << get_info.is_error() << endl;
  cout << get_info.to_string_post() << endl;
  cout << get_info.to_string_rcv() << endl;
  if(get_info.is_error()){
    cout << get_info.to_string_rcv() << endl;
  } else{
    cout << get_info.get<string>("last_irreversible_block_num") << endl;
    cout << get_info.get<string>("head_block_time") << endl;
    boost::posix_time::ptime time = get_info.get<boost::posix_time::ptime>("head_block_time");
    cout << time << endl;

    boost::posix_time::ptime t1 = time + boost::posix_time::seconds(900);
    cout << (boost::posix_time::to_iso_extended_string)(t1) << endl;
    cout << get_info.get<string>("last_irreversible_block_num") << endl;
  }

  // cout << pentagon::get_block::help << pentagon::eosc_command::common_help << endl;
  // pentagon::get_info get_block(
  //   get_block.get<string>("head_block_id"));
  // cout << "is error set = " << get_block.is_error() << endl;
  // cout << get_block.to_string_post() << endl;
  // cout << get_block.to_string_rcv() << endl;
  // if(get_block.is_error()){
  //   cout << get_block.to_string_rcv() << endl;
  // }

  return 0;
}