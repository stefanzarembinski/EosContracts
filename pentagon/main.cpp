#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "pent_core/pent_core.hpp"

int main (int argc, char *argv[]) {

   using namespace std;

   const string server("localhost");
   const string port("8888");
   const string path("/v1/chain/get_info");
   const string postjson("");

   /*
   "":151,
   "":134,
   "":"00000097d4e0e5b1fbacadf470c956e4d85522d54c8d8375709ed68a22bdad65",
   "":"2017-11-22T15:12:45",
   "":"initq",
   "":"1111111111111111111111111111111111111111111111111111111111111111",
   "":"1.00000000000000000"
   */
   struct get_info
   {
      // get_info(){
      //    string resp = pentagon::callEosd(server, port, path, postjson);
      //    try{
      //       pt::read_json(s_in, tree);
      //    }catch(...){
      //       cerr << "Failed to read config json with unknown error";
      //       return 1;
      //    }
      // }

      string head_block_num;
      uint last_irreversible_block_num;
      string head_block_id;
      boost::posix_time::ptime head_block_time;
      string head_block_producer;
      string recent_slots;
      float participation_rate;
   };

   // string resp = pentagon::callEosd(server, port, path, postjson, );
   // namespace pt = boost::property_tree;
   // pt::ptree tree;
   // stringstream s_in;
   // s_in << resp;
   // try{
   //    pt::read_json(s_in, tree);
   // }catch(...){
   //    cerr << "Failed to read config json with unknown error";
   //    return 1;
   // }
   // stringstream s_out;
   // pt::json_parser::write_json(s_out, tree);
   // cout << s_out.str() << endl;
   // string head_block_time = tree.get<string>("head_block_time");
   // cout << head_block_time << endl;
   // head_block_time = boost::replace_all_copy(head_block_time, "-", "");
   // head_block_time = boost::replace_all_copy(head_block_time, ":", "");
   // cout << head_block_time << endl;

   // boost::posix_time::ptime t((boost::posix_time::from_iso_string)(head_block_time));
   // cout << t << endl;
   // boost::posix_time::ptime t1 = t + boost::posix_time::seconds(900);
   // cout << (boost::posix_time::to_iso_extended_string)(t1) << endl;

   return 0;
}