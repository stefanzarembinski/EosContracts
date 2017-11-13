#include <eoslib/types.h>
#include <eoslib/print.hpp>
#include <eoslib/message.hpp>
#include "contract.hpp"

void init()  {
  eosio::print( "Init World!\n" );
}

struct transfer {
  eosio::name from;
  eosio::name to;
  eosio::uint64_t amount;
};

void apply(eosio::uint64_t code, eosio::uint64_t action) {
  eosio::print( 
      "Hello World: ", 
      eosio::name(code), "->", eosio::name(action), "\n" 
    );
  if( action == N(transfer) ) {
      auto message = eosio::current_message<transfer>();
      eosio::print( 
          "Transfer ", 
          message.amount, 
          " from ", message.from, 
          " to ", message.to, "\n" );
  }
}

