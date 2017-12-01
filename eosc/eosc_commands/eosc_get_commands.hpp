#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/property_tree/ptree.hpp>

#include <eosc_config.h>
#include "eosc_command.hpp"

namespace tokenika::eosc
{

  /**
   * @brief Get current blockchain information.
   * 
   */
  class get_info : public eosc_command
  {
  public:
    get_info(
      boost::property_tree::ptree post_json, 
      bool raw = false) : eosc_command(
                                      "/v1/chain/get_block",
                                      post_json,
                                      raw)
    {
      call_eosd();
    }

    get_info() : eosc_command(
                    "/v1/chain/get_info",
                    boost::property_tree::ptree())
    {
      call_eosd();
    }
  };

  // R"EOF(
  // Get current blockchain information
  // Usage: ./eosc get info [OPTIONS]

  // )EOF";

  class get_info_options : public command_options
  {
    public:
      get_info_options(int argc, const char **argv)
        : command_options(argc, argv){}

    protected:      
      const char* get_usage(){
        return R"EOF(
Get current blockchain information
Usage: ./eosc get info [OPTIONS]

)EOF";}

      virtual bool set_json(boost::program_options::variables_map &vm){
        return true;
      }

      virtual eosc_command get_command(bool is_raw){
        return get_info(post_json, is_raw);
      }

      virtual void get_example(){
        get_info get_info;
        std::cout << R"EOF(
Invoke 'get_info' command:
get_info get_info;
)EOF" << std::endl;
        std::cout << get_info.to_string_rcv() << std::endl;
      }
  };

  /**
   * @brief Retrieve a full block from the blockchain.
   * 
   */
  class get_block : public eosc_command
  {
  public:

    get_block(
      boost::property_tree::ptree post_json, 
      bool raw = false) : eosc_command(
                                      "/v1/chain/get_block",
                                      post_json,
                                      raw)
    {
      call_eosd();
    }

    get_block(uint block_number, bool raw = false) : eosc_command(
                                      "/v1/chain/get_block",
                                      boost::property_tree::ptree(),
                                      raw)
    {
      post_json.put("block_num_or_id", block_number);
      call_eosd();
    }

    get_block(std::string id, bool raw = false) : eosc_command(
                                      "/v1/chain/get_block",
                                      boost::property_tree::ptree(),
                                      raw)
    {
      post_json.put("block_num_or_id", id);
      call_eosd();
    }
  };

  class get_block_options : public command_options
  {
    public:
      get_block_options(int argc, const char **argv)
        : command_options(argc, argv){}

    protected:      
      const char* get_usage(){
        return R"EOF(
Retrieve a full block from the blockchain
Usage: ./eosc get block block [OPTIONS]

)EOF";}

      int n;
      std::string id;

      virtual boost::program_options::options_description options(){
        boost::program_options::options_description special("");
        special.add_options()
        ("block_num,n", 
            boost::program_options::value<int>(&n), 
            "Block number")
        ("block_id,i",
            boost::program_options::value<std::string>(&id), 
            "Block id");
        return special;
      }

      virtual bool set_json(boost::program_options::variables_map &vm){
        bool ok = false;
        if(vm.count("block_num")){
          post_json.put("block_num_or_id", n);
          ok = true;
        } else if (vm.count("block_id")){
          post_json.put("block_num_or_id", id);
          ok = true;
        }
        return ok;
      }

      virtual eosc_command get_command(bool is_raw){
        return get_block(post_json, is_raw);
      }

      virtual void get_example(){
        get_info get_info;
        std::cout << R"EOF(
Invoke 'get_info' command:
get_info get_info;
)EOF" << std::endl;

        std::cout << get_info.to_string_rcv() << std::endl;
        get_block get_block(
          get_info.get<int>("last_irreversible_block_num"));
        std::cout << R"EOF(
Use reference to the recentmost block:
get_block get_block(
  get_info.get<int>("last_irreversible_block_num"));
)EOF" << std::endl;
        std::cout << get_block.to_string_rcv() << std::endl;
      }
  };
}
