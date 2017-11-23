
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../pent_core/pent_core.hpp"
#include <pent_config.h>
#include "eosc_commands.hpp"

namespace pentagon{

   get_info::get_info(){
      boost::property_tree::ptree tree;
      boost::property_tree::read_json(CONFIG_JSON, tree);
   }
}