cmake_minimum_required (VERSION 3.6)
project (CurrencyContract)
include(../../config.cmake)

set(INSTALL_DIR "${PROJECT_SOURCE_DIR}/../../install")
message(STATUS "INSTALL_DIR: ${INSTALL_DIR}")

include_directories(${EOSIO_INSTALL_DIR}/contracts)
include_directories(${INSTALL_DIR}/include)

add_executable(${PROJECT_NAME} currency.hpp currency.cpp main.cpp)


target_link_libraries(${PROJECT_NAME} ${INSTALL_DIR}/lib/libpentagon1.a)
target_link_libraries(${PROJECT_NAME} ${INSTALL_DIR}/lib/libmessage.a)
target_link_libraries(${PROJECT_NAME} ${INSTALL_DIR}/lib/libprint.a)
target_link_libraries(${PROJECT_NAME} ${INSTALL_DIR}/lib/libsystem.a)
target_link_libraries(${PROJECT_NAME} ${INSTALL_DIR}/lib/libdb.a)


install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${INSTALL_DIR}/bin)
