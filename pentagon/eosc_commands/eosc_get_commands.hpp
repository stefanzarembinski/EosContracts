#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/property_tree/ptree.hpp>

#include "../pent_core/pent_core.hpp"
#include <pent_config.h>
#include "eosc_commands.hpp"

namespace pentagon{ 
/**
 * @brief 
 * 
 */
  class get_info : public eosc_command{

    public:
      static constexpr const char* help =
R"EOF(
Get current blockchain information
Usage: ./eosc get info [OPTIONS]

Options:
)EOF";
      std::string 
      get_info(){
        if(!eosc_command_json(
          "/v1/chain/get_info", 
          post_json, rcv_json)){
            is_error_set = true;
            return;
        } 
      }
  };

/**
 * @brief 
 * 
 */
  class get_block : public eosc_command {
    public:
      static constexpr const char* help =
R"EOF(
Retrieve a full block from the blockchain
Usage: ./eosc get block block


Positionals:
  block TEXT                  The number or ID of the block to retrieve
Options:
)EOF";

      get_block(uint block_number){

      }
      get_block(std::string id){

      }
  };


}
