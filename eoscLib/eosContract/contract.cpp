#include <eoslib/eos.hpp>

#include "contract.hpp"
//#include "truffle.hpp"

extern "C" {
    void init()  {
       eosio::print( "init contract\n" );
    }

   struct transfer {
      eosio::name from; //types.hpp struct name
      eosio::name to;
      eosio::uint64_t amount;
   };

   void apply( eosio::uint64_t code, eosio::uint64_t action ) {
      eosio::print( 
         "code: ", code, "; ",
         " name(code): ", eosio::name(code), "; ", //name is defined in types.hpp
         "\n",
         "action: ", action, "; ", 
         " name(action): ", eosio::name(action), 
         "\n\n"
         );
      if( action == N(transfer) ) {
         // auto message = eosio::current_message<transfer>();
         // eosio::print( 
         //    "Transfer ", 
         //    message.amount, 
         //    " account1 ", message.account1, 
         //    " account2 ", message.account2, "\n" );
      }
   }
}