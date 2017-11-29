#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/program_options.hpp>

#define ERROR "error" // Error json key

namespace tokenika::eosc{

  extern boost::posix_time::ptime strtotime(const std::string str);
  
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
    
  template<typename Type> 
  Type get1(boost::property_tree::ptree json,
    const boost::property_tree::ptree::path_type & path);

  class eosc_command {
      std::string path;
      boost::property_tree::ptree rcv_json;
      bool is_error_set;
      bool is_raw;

    protected:
      boost::property_tree::ptree post_json;

    public:
      // static boost::program_options::options_description 
      //   options(int argc, const char* argv[]){
      //   using namespace boost::program_options;

      //   try{
      //     options_description desc{"Options"};
      //     desc.add_options()
      //       ("help,h", "Help screen")
      //       ("default,d", "Use default args")
      //       ("raw", "Not pretty print")
      //       ("post,p", "Print post json")
      //       ("json,j", "Print received json")
      //       ("unreg", "Unrecognized options");
      //   } catch (const error &ex){
      //     std::cerr << ex.what() << std::endl;
      //   }
      // }
      // static void xxxx(
      //     boost::program_options::options_desc,
      //     boost::program_options::variables_map vm,
      //     const char* usage)
      //   {
      //   using namespace std;
// R"EOF(
// Get current blockchain informatiojsonn
// Usage: ./eosc get info [OPTIONS]

// )EOF";

// R"EOF(
// Retrieve a full block from the blockchain
// Usage: ./eosc get block block


// Positionals:
//   block TEXT                  The number or ID of the block to retrieve
// Options:
// )EOF";

      //   if (vm.count("help")){
      //     cout << usage << std::endl;
      //     cout << desc << std::endl;
      //   } else if (vm.count("default")){
      //     get_info inst(vm);
      //     std::cout << "arguments:" << std::endl;
      //     cout << inst.to_string_post() << endl << endl;
      //     cout << "result:" << endl;
      //     cout << inst.to_string_rcv() << endl;
      //   } else if (vm.count("post")){
      //     get_info inst(vm);
      //     cout << inst.to_string_post() << endl;
      //   } else if (vm.count("json")){
      //     get_info inst(vm);
      //     cout << inst.to_string_rcv() << endl;
      //   } else if (vm.count("unreg")){
      //     std::cout << usage << std::endl;
      //     std::cout << desc << std::endl;
      //   }
      // }

      eosc_command(
          std::string path_, 
          boost::property_tree::ptree post_json_,
          bool is_raw_ = false)
        {
        is_error_set = false;
        path = path_;
        post_json = post_json_;
        is_raw = is_raw_;
      }

      void call_eosd(){
        if(!eosc_command_json(path, post_json, rcv_json)){
            is_error_set = true;
        }
      }

      bool is_error() const {
        return is_error_set;
      }

      boost::property_tree::ptree get_resp_json() const {
        return rcv_json;
      }

      std::string to_string_post() const;
      std::string to_string_rcv() const;
      template<typename Type> 
      Type get(const boost::property_tree::ptree::path_type & path) const{
        return get1<Type>(rcv_json, path);
    }  
  };
}