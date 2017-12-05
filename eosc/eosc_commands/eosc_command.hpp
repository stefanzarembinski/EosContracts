/**
 * @file eosc_command.hpp
 * @copyright defined in resources/LICENSE.txt
 * @defgroup eosc Tokenika-EOS Command Line Client Reference
 * @brief Tool for sending transactions and querying state from EOS blockchain
 * @ingroup eosc
 * 
 * @brief Base definitions.
 * 
 * Defines base classes of the project, and helper methods.
 */

#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/program_options.hpp>

#define ERROR "error" // Error json key

namespace tokenika::eosc{

  /**
   * @brief Converts EOS time string to 'boost::posix_time'.
   * 
   * EOS time is a string, for example `2017-07-18T20:16:36`. For processing, 
   * it is converted to the boost `ptime`.
   * 
   * @param str EOS time string.
   * @return boost::posix_time::ptime 
   */
  extern boost::posix_time::ptime strToTime(const std::string str);

  /**
   * @brief Printout formater.
   * 
   * For example, `output("timestamp", "%s", "2017-07-18T20:16:36")` produces
   * `##           timestamp: 2017-07-18T20:16:36`
   * 
   * @param label 
   * @param format 
   * @param ... 
   */
  extern void output(const char* label, const char* format, ...);

  /**
   * @brief Given a json, gets EOS blockchain responce.
   * 
   * Given a json and a command path, for example `/v1/chain/GetInfo`, 
   * gets EOS blockchain responce.
   * 
   * @param path command path
   * @param postJson json posted
   * @param jsonRcv json received
   * @return true if EOS blockchain responce is normal
   * @return false if EOS blockchain responce is not normal
   */
  extern bool eoscCommandJson(
    std::string path, 
    boost::property_tree::ptree &postJson, 
    boost::property_tree::ptree &jsonRcv);

  /**
   * @brief Given a json, gets EOS blockchain responce.
   * 
   * Given a json tree and a command path (for example `/v1/chain/GetInfo`),
   * and EOS blockchain communication port (for example `8888`), 
   * and EOS blockchain server name (for example `localhost`),
   * gets EOS blockchain responce.
   * 
   * @param server EOS blockchain server name
   * @param port EOS blockchain communication port
   * @param path command path
   * @param postJson json to be posted
   * @param jsonRcv json to be filled with received data
   */
  extern void callEosd(
    std::string server, 
    std::string port, 
    std::string path,
    boost::property_tree::ptree &postJson,
    boost::property_tree::ptree &jsonRcv);
    
  /**
   * @brief Given a json tree, returns the <Type>value of a given path.
   * 
   * @tparam Type type of the called value
   * @param json json tree
   * @param path path of the given tree
   * @return Type 
   */
  template<typename Type> 
  Type getJsonPath(boost::property_tree::ptree json,
    const boost::property_tree::ptree::path_type & path);
  
  /**
   * @brief Given a text json tree, returns the equivalent `boost ptree`. 
   * 
   * @param json 
   * @return boost::property_tree::ptree 
   */
  extern boost::property_tree::ptree stringToPtree(
    std::string json);
  
  /**
   * @brief Basic connection to the blockchain
   * 
   * Given a command path (for example `/v1/chain/GetBlock`), and a json tree
   * (for example {"block_num_or_id"="25"}), 
   * connects to the blockchain and receive a json reflacting an aspect of the
   * blockchain state.
   * 
   * `EoscCommand` is the superclass for any specific command class in this 
   * library.
   * 
   * Parameters of the connection used are specified in file `eosc_config.json`
   * in the root directory of the project.
   * 
   */
  class EoscCommand 
  {
      std::string path;
      boost::property_tree::ptree jsonRcv;
      bool isErrorSet = false;
      bool isRaw;

    protected:
      boost::property_tree::ptree postJson;

    public:
      /**
       * @brief Just initiates members and calls the blockchain
       * 
       * @param path command path, for example `/v1/chain/GetBlock`
       * @param postJson json tree, for example {"block_num_or_id"="25"}
       * @param isRaw boolean, determines printout of the to-string methods
       */
      EoscCommand(
          std::string path, 
          boost::property_tree::ptree postJson,
          bool isRaw = false) 
            : path(path), postJson(postJson), isRaw(isRaw) 
      {
        if(!eoscCommandJson(path, postJson, jsonRcv)){
             isErrorSet = true;
        }
      }

      bool isError() const {
        return isErrorSet;
      }

      boost::property_tree::ptree getRcvJson() const {
        return jsonRcv;
      }

      std::string toStringPost() const;
      std::string toStringRcv() const;

      /**
       * @brief Returns a value of a path of the received json.
       * 
       * @tparam Type 
       * @param path 
       * @return Type get 
       */
      template<typename Type> 
      Type get(const boost::property_tree::ptree::path_type & path) const{
        return getJsonPath<Type>(jsonRcv, path);
    }  
  };

  //http://boost.cowic.de/rc/pdf/program_options.pdf
  /**
   * @brief Command line options base.
   * 
   */
  class CommandOptions
  {
    int argc;
    const char **argv;
    std::string json;

    protected:

      boost::property_tree::ptree postJson;
      virtual const char* get_usage(){return "";}

      virtual boost::program_options::options_description options(){
        boost::program_options::options_description special("");
        return special;
      }

      virtual void
        set_pos_desc(boost::program_options::positional_options_description& 
          pos_descr){}

      virtual bool set_json(boost::program_options::variables_map &vm){
        return false;
      }

      virtual EoscCommand get_command(bool isRaw){
        return EoscCommand("", postJson);
      }

      virtual void get_example(){}

      virtual void get_output(EoscCommand command){
        std::cout << command.toStringRcv() << std::endl;
      }

    void common_options(boost::program_options::options_description& common){
      common.add_options()
        ("help,h", "Help screen")
        ("json,j", 
          boost::program_options::value<std::string>(&json),
          "Json argument")
        ("received,v", "Print received json")        
        ("raw,r", "Not pretty print")
        ("example,e", "Usage example");
    }

    public:
      CommandOptions(int argc, const char **argv) : argc(argc), argv(argv) {}
      void go();
  };

  template<class T> static void set_options(std::vector<std::string> strVector){
    std::vector<const char*> cStrArray;
    cStrArray.reserve(strVector.size());
    for(int index = 0; index < strVector.size(); ++index)
      {
        cStrArray.push_back(strVector[index].c_str());
      }
    T(cStrArray.size(), &cStrArray[0]).go();
  }
}