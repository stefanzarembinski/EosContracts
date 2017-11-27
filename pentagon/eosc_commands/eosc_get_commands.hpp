#ifndef EOS_GET_COMMANDS_HPP___
#define EOS_GET_COMMANDS_HPP___

#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/property_tree/ptree.hpp>

#include "../pent_core/pent_core.hpp"
#include <pent_config.h>
#include "eosc_commands.hpp"

namespace pentagon{ 

  class get_info : public eosc_command{
    
    public:
      std::string get_help(){
        return std::string(R"EOF(
Get current blockchain information
Usage: ./eosc get info [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
)EOF");

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

  class get_block {
    public:
      get_block(uint block_number){

      }
      get_block(std::string id){

      }
  };
}

#endif //EOS_GET_COMMANDS_HPP___