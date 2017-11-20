cmake_minimum_required (VERSION 3.6)
project (CurrencyContract)
include(../eosContracts.cmake)

include_directories("${PROJECT_SOURCE_DIR}/eoscContract")
include_directories("${EOSIO_INSTALL_DIR}/contracts")
add_executable(${PROJECT_NAME} currency.hpp main.cpp currency.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/libmessage.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/libprint.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/libsystem.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/libdb.a)

