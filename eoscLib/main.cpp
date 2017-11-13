#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "config.h"
#include "eosContract/contract.hpp"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

int main (int argc, char *argv[]){
   init();
   

   
   eosio::uint64_t code = 0;
   eosio::uint64_t action = N(transfer);

   return 0;
}