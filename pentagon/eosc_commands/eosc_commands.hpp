
#include "boost/date_time/posix_time/posix_time.hpp"

namespace pentagon{

   class get_info {
      public:
         get_info();
         std::string head_block_num;
         uint last_irreversible_block_num;
         std::string head_block_id;
         boost::posix_time::ptime head_block_time;
         std::string head_block_producer;
         std::string recent_slots;
         float participation_rate;
   };
}