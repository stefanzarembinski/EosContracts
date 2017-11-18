cmake_minimum_required (VERSION 3.6)
project (CurrencyContract)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(../eosContracts.cmake)

include_directories("${PROJECT_SOURCE_DIR}/eoscContract")
include_directories("/mnt/hgfs/Workspaces/EOS/eos/contracts")
add_executable(${PROJECT_NAME} currency.hpp main.cpp currency.cpp)
