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

// R"EOF(
// Get current blockchain information
// Usage: ./eosc get info [OPTIONS]

// )EOF";

/**
 * @brief Retrieve a full block from the blockchain.
 * 
 */
class get_block : public eosc_command
{
public:

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

class get_block_options
{
  public:
    boost::program_options::options_description desc{"Options"};
    boost::property_tree::ptree post_json;

    void get_example(){
      get_info get_info;
      std::cout << "get info:" << std::endl;
      std::cout << get_info.to_string_rcv() << std::endl;
      get_block get_block(
        get_info.get<int>("last_irreversible_block_num"));
      std::cout << "get block:" << std::endl;
      std::cout << get_block.to_string_rcv() << std::endl;
    }

    const char* get_usage(){
      return R"EOF(
Retrieve a full block from the blockchain
Usage: ./eosc get block block

)EOF";
    }

    void add_options(boost::property_tree::ptree &post_json){
      int n;
      std::string id;      
      desc.add_options()
        ("block_num,n", 
          boost::program_options::value<int>(&n), 
          "Block number")
        ("block_id,i",
          boost::program_options::value<std::string>(&id), 
          "Block id");
    }

    get_block_options(int argc, const char **argv)
    {
        try{

          bool is_raw = false;
          bool is_print = false;
          //add_options();

      int n;
      std::string id;



          desc.add_options()
            ("block_num,n", 
              boost::program_options::value<int>(&n), 
              "Block number")
            ("block_id,i",
              boost::program_options::value<std::string>(&id), 
              "Block id")

            ("help,h", "Help screen")
            ("example", "Using example")
            ("raw", "Not pretty print")
            ("json", "Print received json")
            ("unreg", "Unrecognized options");

          boost::program_options::variables_map vm;
          store(parse_command_line(argc, argv, desc), vm);
          notify(vm);

          is_raw = vm.count("raw");
          is_print = vm.count("json");

          if (vm.count("help")){
            std::cout << get_usage() << std::endl;
            std::cout << desc << std::endl;
          } else if(vm.count("example") || vm.count("block_num") || vm.count("block_id")){
            if (vm.count("example")){
              get_example();
            } else if(vm.count("block_num") || vm.count("block_id")){
              if(vm.count("block_num")){
                get_block get_block(n, is_raw);
                std::cout << get_block.to_string_rcv() << std::endl;
              } else if(vm.count("block_id")){
                get_block get_block(id, is_raw);
                std::cout << get_block.to_string_rcv() << std::endl;
              }
            } else {
              std::cout << get_usage()<< std::endl;
              std::cout << desc << std::endl;           
            }
          } else if (vm.count("unreg")){
            std::cout << get_usage() << std::endl;
            std::cout << desc << std::endl;
          }

        } catch (const boost::program_options::error &ex){
          std::cerr << ex.what() << std::endl;
        }
    }

    // struct convert{
    //   const char** argv;
    //   convert(std::vector<std::string> &strVector){
    //     std::vector<const char *> cStrArray;
    //     cStrArray.reserve(strVector.size());
    //     for(int index = 0; index < strVector.size(); ++index)
    //     {
    //       cStrArray.push_back(strVector[index].c_str());
    //     }
    //     argv = &cStrArray[0];
    //   }
    // };

    static void get_block_options_(std::vector<std::string> strVector){
      std::vector<const char*> cStrArray;
      cStrArray.reserve(strVector.size());
      for(int index = 0; index < strVector.size(); ++index)
        {
          cStrArray.push_back(strVector[index].c_str());
        }
      get_block_options(cStrArray.size(), &cStrArray[0]);
    }     
};
}
