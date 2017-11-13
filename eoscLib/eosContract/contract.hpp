#include <eoslib/types.hpp>

extern "C" {
   void init();
   void apply(eosio::uint64_t code, eosio::uint64_t action );
} 