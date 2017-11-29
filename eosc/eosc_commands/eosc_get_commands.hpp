#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/property_tree/ptree.hpp>

#include <eosc_config.h>
#include "eosc_commands.hpp"

namespace tokenika::eosc
{

/**
 * @brief Get current blockchain information.
 * 
 */
class get_info : public eosc_command
{
public:
  get_info() : eosc_command(
                   "/v1/chain/get_info",
                   boost::property_tree::ptree())
  {
    call_eosd();
  }
};

/**
 * @brief Retrieve a full block from the blockchain.
 * 
 */
class get_block : public eosc_command
{
public:
  get_block(uint block_number) : eosc_command(
                                     "/v1/chain/get_block",
                                     boost::property_tree::ptree())
  {
    post_json.put("block_num_or_id", block_number);
    call_eosd();
  }

  get_block(std::string id) : eosc_command(
                                     "/v1/chain/get_block",
                                     boost::property_tree::ptree())
  {
    post_json.put("block_num_or_id", id);
    call_eosd();
  }
};

class get_block_options
{
  using namespace boost::program_options;

  public:
    options_description desc;
    variables_map vm;

    get_block_options(int argc, const char *argv[]){
      

    }
};
}
