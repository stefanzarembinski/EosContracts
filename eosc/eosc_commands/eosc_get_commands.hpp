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

  class get_block_options
  {
    boost::property_tree::ptree post_json;
    int n;
    std::string id;

    public:

      const char* get_usage(){
        return R"EOF(
Retrieve a full block from the blockchain
Usage: ./eosc get block block [OPTIONS]

)EOF";
      }

      boost::program_options::options_description options(){
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

      bool set_json(boost::program_options::variables_map &vm){
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

      eosc_command get_command(bool is_raw){
        return get_block(post_json, is_raw);
      }

      void get_example(){
        get_info get_info;
        std::cout << "get info:" << std::endl;
        std::cout << get_info.to_string_rcv() << std::endl;
        get_block get_block(
          get_info.get<int>("last_irreversible_block_num"));
        std::cout << "get block:" << std::endl;
        std::cout << get_block.to_string_rcv() << std::endl;
      }
  };

  //http://boost.cowic.de/rc/pdf/program_options.pdf
  class command_options
  {
    boost::program_options::options_description desc{"Options"};
    tokenika::eosc::get_block_options special;

    void common_options(boost::program_options::options_description& common){
      common.add_options()
        ("help,h", "Help screen")
        ("example", "Usage example") 
        ("raw", "Not pretty print")
        ("json", "Print received json")
        ("unreg", "Unrecognized options");
    }
    
    public:
      command_options(int argc, const char **argv)
      {
        try{
          bool is_raw = false;
          bool is_print = false;

          boost::program_options::options_description common("");
          common_options(common);
          desc.add(special.options()).add(common);

          boost::program_options::variables_map vm;
          store(parse_command_line(argc, argv, desc), vm);
          notify(vm);
        
          is_raw = vm.count("raw");
          is_print = vm.count("json");

          if (vm.count("help")){
            std::cout << special.get_usage() << std::endl;
            std::cout << desc << std::endl;
          } else if(vm.count("example")){
              special.get_example();
          } else if(special.set_json(vm)){
            eosc_command command = special.get_command(is_raw);
            std::cout << command.to_string_rcv() << std::endl;
          } else if (vm.count("unreg")){
            std::cout << special.get_usage() << std::endl;
            std::cout << desc << std::endl;
          }
        } catch (const boost::program_options::error &ex){
          std::cerr << ex.what() << std::endl;
        }
      }

      static void set_options(std::vector<std::string> strVector){
        std::vector<const char*> cStrArray;
        cStrArray.reserve(strVector.size());
        for(int index = 0; index < strVector.size(); ++index)
          {
            cStrArray.push_back(strVector[index].c_str());
          }
        command_options(cStrArray.size(), &cStrArray[0]);
      }     
  };
}
