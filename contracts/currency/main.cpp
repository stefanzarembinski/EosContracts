
#include "currency.hpp"
#include <pentagon1.hpp>

int main (int argc, char *argv[]) {
   //init();

   fprintf(stdout, "size(unsigned long long): %d\n",
      sizeof(unsigned long long));

   fprintf(stdout, "size(eosio::uint64_t): %d\n",
      sizeof(eosio::uint64_t));
   
   fprintf(stdout, "%s\n", pentagon::eos_name(eosio::uint64_t(5093418677655568384ULL)).c_str());
   fprintf(stdout, "%s\n", pentagon::eos_name(eosio::uint64_t(14829575313431724032ULL)).c_str());
   const char* currency = "currency";
   fprintf(stdout, "%lu\n", pentagon::eos_name(currency));
   const char* transfer = "transfer";
   fprintf(stdout, "%lu\n", pentagon::eos_name(transfer));

   apply(
      eosio::uint64_t(pentagon::eos_name(currency)), 
      eosio::uint64_t(pentagon::eos_name(transfer)));
}