#ifndef EOS_GET_COMMANDS_HPP___
#define EOS_GET_COMMANDS_HPP___

#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/property_tree/ptree.hpp>

#include "../pent_core/pent_core.hpp"
#include <pent_config.h>
#include "eosc_commands.hpp"

namespace pentagon{ 
  // template<typename Type> Type get1(boost::property_tree::ptree json,
  //   const boost::property_tree::ptree::path_type & path){
  //   return json.get<Type>(path);
  // }

  // template<> boost::posix_time::ptime get1(boost::property_tree::ptree json,
  //     const boost::property_tree::ptree::path_type & path){
  //     return strtotime(json.get<std::string>(path));
  // }


  class get_info {
    boost::property_tree::ptree post_json;
    boost::property_tree::ptree rcv_json;
    std::string* error_ptr = NULL;

    public:
      std::string get_error_msg() const {
        if(error_ptr == NULL){
          return "Error is not set";
        }
        return *error_ptr;
      }

      boost::property_tree::ptree get_resp_json() const {
        return rcv_json;
      }

      std::string to_string_post(bool pretty = true) const {
        std::stringstream ss;
        boost::property_tree::json_parser::
          write_json(ss, post_json, false);
      }

      std::string to_string_rcv(bool pretty = true) const {
        std::stringstream ss;
        boost::property_tree::json_parser::
          write_json(ss, post_json, false);
      }

      template<typename Type> Type get(
        const boost::property_tree::ptree::path_type & path) const{
        return get1<Type>(rcv_json, path);
      }

      get_info(){
        if(!eosc_command_json(
          "/v1/chain/get_info", 
          post_json, rcv_json)){
            std::string error = rcv_json.get<std::string>(ERROR);
            error_ptr = &error;
            return;
        } 
      }
  };

  //   class get_block {
  //   public:
  //     boost::posix_time::ptime timestamp;
  //     std::string id;      
  //     uint block_num;

  //     boost::property_tree::ptree rcv_json;

  //     get_info(uint block_num; uint id){
  //       std::stingstream postjson;
  //       postjson << "'" << '{' << '}';

  //       if(!eosc_command_json(
  //         "/v1/chain/get_block", 
  //         "", 
  //         rcv_json)){
  //         std::cerr << rcv_json.get<std::string>(ERROR) << std::endl;
  //         return;
  //       } 

  //       timestamp = strtotime(rcv_json.get("timestamp", ""))
  //       id = rcv_json.get("id", "")
  //       block_num = rcv_json.get("block_num", 0);
  //     }
  // };
}

#endif //EOS_GET_COMMANDS_HPP___