### CMake tuning
* CMake honors the environment variables CC and CXX upon detecting the C and C++ compiler to use:
```
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
## cmake ..
## -- The C compiler identification is Clang
## -- The CXX compiler identification is Clang

```
ERROR: 
/mnt/hgfs/Workspaces/EOS/EosContracts/utils/main.cpp:50:27: warning: range-based for loop is a C++11 extension [-Wc++11-extensions]

With the following setting, the error remains!!!!!!!!!
```
SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c++11")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
```
* System wide C++ change on Ubuntu:
```
sudo update-alternatives --config c++
##   Selection    Path              Priority   Status
## ------------------------------------------------------------
## * 0            /usr/bin/g++       20        auto mode
##   1            /usr/bin/clang++   10        manual mode
##   2            /usr/bin/g++       20        manual mode
```
## Compile errors

### types.h
```cpp
namespace eosio{ // originally, numerous conflicts with standard libraries.
   typedef long long            int64_t;
   typedef unsigned long long   uint64_t;
   typedef unsigned long        uint32_t;
   typedef unsigned short       uint16_t; 
   typedef long                 int32_t;
   typedef unsigned __int128    uint128_t;
   typedef __int128             int128_t;
   typedef unsigned char        uint8_t;
   typedef char                 int8_t;
   typedef short                int16_t;
   typedef unsigned int         size_t;
}
```


### body of constexpr function ... not a return-statement

/eos/contracts/eoslib/types.hpp:52:4: error: body of constexpr function ‘constexpr eosio::uint64_t eosio::string_to_name(const char*)’ not a return-statement
    }

```cpp
static constexpr char char_to_symbol( char c ) {
      if( c >= 'a' && c <= 'z' )
         return (c - 'a') + 6;
      if( c >= '1' && c <= '5' )
         return (c - '1') + 1;
      return 0;message
   }
```

From [cppreference](# http://en.cppreference.com/w/cpp/language/constexpr):

the function body must be either deleted or defaulted or contain only the following:
* null statements (plain semicolons)
* static_assert declarations
* typedef declarations and alias declarations that do not define classes or enumerations
* using declarations
* using directives
* **exactly one return statement**.

The same there:
```
   static constexpr eosio::uint64_t string_to_name( const char* str ) {

      eosio::uint32_t len = 0;
      while( str[len] ) ++len;

      eosio::uint64_t value = 0;

      for( eosio::uint32_t i = 0; i <= 12; ++i ) {
         eosio::uint64_t c = 0;
         if( i < len && i <= 12 ) c = char_to_symbol( str[i] );

         if( i < 12 ) {
            c &= 0x1f;
            c <<= 64-5*(i+1);
         }
         else {
            c &= 0x0f;
         }

         value |= c;
      }

      return value;
   }
```
I remove the constexpr declaration.

### types.h typedef eosio::uint32_t time;

eos/contracts/eoslib/types.h:35:25: error: ‘typedef eosio::uint32_t time’ 
redeclared as different kind of symbol
 typedef eosio::uint32_t time;

In file included from /usr/include/pthread.h:24:0,

## Letter

We are interested in building a development tool for EOS contracts that could be comparable to the Truffle device.

Our effort could be much easer if you would approve the following formal changes in the code of the *contracts* part:

* Some of the type definitions in *eoslib/types.h* conflict with **standard libraries**. Could not they be put into a namespace:
```
namespace eosio{
   typedef long long            int64_t;
   typedef unsigned long long   uint64_t;
   typedef unsigned long        uint32_t;
   typedef unsigned short       uint16_t; 
   typedef long                 int32_t;
   typedef unsigned __int128    uint128_t;
   typedef __int128             int128_t;
   typedef unsigned char        uint8_t;
   typedef char                 int8_t;
   typedef short                int16_t;
   typedef unsigned int         size_t;
   typedef eosio::uint32_t      time;
}
```
* The same with two functions in *system.h*, namely *assert* and *now*.

* The formal definition of the *constexpr* function From [cppreference](#http://en.cppreference.com/w/cpp/language/constexpr):
    * the function body must be either deleted or defaulted or contain only the following:
        * null statements (plain semicolons)
        * static_assert declarations
        
        * typedef declarations and alias declarations that do not define classes or enumerations
        * using declarations
        * using directives
        * exactly one return statement.
In *eoslib/types.hpp* there are *constexpr* functions that do not adhere to the definition, and therefore the cause compile errors like this:
```
/eos/contracts/eoslib/types.hpp:52:4: error: body of constexpr function ‘constexpr eosio::uint64_t eosio::string_to_name(const char*)’ not a return-statement
    }
```
Could you consider replacing them with regular functions?
