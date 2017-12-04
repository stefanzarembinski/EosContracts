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
   * #include <stdio.h>
   * #include <stdlib.h>
   * #include <iostream>
   * #include <string>
   * #include "eosc_commands/eosc_get_commands.hpp"
   * 
   * int main(int argc, char *argv[])
   * {
   * tokenika::eosc::get_info get_info; // Call 'eosd' for 'get info'.
   * std::cout << get_info.to_string_rcv() << std::endl; // Print the response.
   * return 0;
   * }
   * 
   */
  class get_info : public eosc_command
  {
  public:
  
    get_info(
      boost::property_tree::ptree post_json, 
      bool raw = false) 
      : eosc_command(
          "/v1/chain/get_info",
          post_json,
          raw)
    {
      call_eosd();
    }

  };

  class get_info_options : public command_options
  {
    public:
      get_info_options(int argc, const char **argv)
        : command_options(argc, argv){}

    protected:      
      const char* get_usage(){
        return R"EOF(
Get current blockchain information
Usage: ./eosc get info [Options]
Usage: ./eosc get info [-j '{}'] [OPTIONS]
)EOF";}

      virtual bool set_json(boost::program_options::variables_map &vm){
        return true;
      }

      virtual eosc_command get_command(bool is_raw){
        return get_info(post_json, is_raw);
      }

      virtual void get_output(tokenika::eosc::eosc_command command){
        output("head block", "%d", command.get<int>("head_block_num"));
        output("head block time", "%s", command.get<int>("head_block_time"));
        output("last irreversible block", "%d", command.get<int>("last_irreversible_block_num"));
      }

      virtual void get_example(){
        boost::property_tree::ptree post_json;
        get_info get_info(post_json);
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
   * @verbatim
   * #include <stdio.h>
   * #include <stdlib.h>
   * #include <iostream>
   * #include <string>
   * #include "eosc_commands/eosc_get_commands.hpp"
   * 
   * int main(int argc, char *argv[])
   * {
   * tokenika::eosc::get_info get_info; // Call 'eosd' for 'get info'.
   * tokenika::eosc::get_block get_block( // Call 'eosd' for 'get block', the last one.
   * get_info.get<int>("last_irreversible_block_num"));
   * std::cout << get_block.to_string_rcv() << std::endl; // Print the response.
   * return 0;
   * }
   * @endverbatim
   */
  class get_block : public eosc_command
  {
  public:

    get_block(boost::property_tree::ptree post_json, bool raw = false) 
        : eosc_command(
          "/v1/chain/get_block",
          post_json,
          raw)
    {
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
Usage: ./eosc get block [block_num] [Options]
Usage: ./eosc get block [-j '{"block_num_or_id":"int | string"}'] [OPTIONS]
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

      virtual void
        set_pos_desc(boost::program_options::positional_options_description& 
        pos_desc){
        pos_desc.add("block_num", 1);
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

      virtual void get_output(eosc_command command){
        output("block number", "%d", command.get<int>("block_num"));
        output("timestamp", "%s", command.get<std::string>("timestamp").c_str());
        output("ref block prefix", "%s",command.get<std::string>("refBlockPrefix").c_str());
      }

      virtual void get_example(){
        boost::property_tree::ptree get_info_post_json;
        get_info get_info(get_info_post_json);
        std::cout << R"EOF(
Invoke 'get_info' command:
get_info get_info;
)EOF" << std::endl;

        std::cout << get_info.to_string_rcv() << std::endl;
        boost::property_tree::ptree get_block_post_json;
        get_block_post_json.put("block_num_or_id", 25);
        get_block get_block(get_block_post_json);
        std::cout << R"EOF(
Use reference to the last block:
get_block get_block(
  get_info.get<int>("last_irreversible_block_num"));
)EOF" << std::endl;
        std::cout << get_block.to_string_rcv() << std::endl;
      }
  };
}
