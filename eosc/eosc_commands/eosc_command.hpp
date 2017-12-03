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

  extern void output(const char* label, const char* format, ...);

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

  extern boost::property_tree::ptree string_to_ptree(
    std::string json);

  class eosc_command 
  {
      std::string path;
      boost::property_tree::ptree rcv_json;
      bool is_error_set = false;
      bool is_raw;

    protected:
      boost::property_tree::ptree post_json;

    public:
      eosc_command(
          std::string path, 
          boost::property_tree::ptree post_json,
          bool is_raw = false) 
            : path(path), post_json(post_json), is_raw(is_raw) {}
      
      eosc_command(
          std::string path, 
          std::string json,
          bool is_raw = false) 
            : path(path), is_raw(is_raw) 
      {
        post_json = string_to_ptree(json);
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

  //http://boost.cowic.de/rc/pdf/program_options.pdf
  class command_options
  {
    int argc;
    const char **argv;

    protected:
      boost::property_tree::ptree post_json;
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

      virtual eosc_command get_command(bool is_raw){
        return eosc_command("", post_json);
      }

      virtual void get_example(){}

      virtual void get_output(eosc_command command){
        std::cout << command.to_string_rcv() << std::endl;
      }

    std::string json;
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
      command_options(int argc, const char **argv) : argc(argc), argv(argv) {}
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