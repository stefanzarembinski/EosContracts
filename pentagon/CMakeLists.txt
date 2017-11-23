cmake_minimum_required (VERSION 3.8)
project (pentagon)
include(../pent_config.cmake)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(CONFIG_JSON "\"${PROJECT_SOURCE_DIR}/../pent_config.json\"")
configure_file (
   "${PROJECT_SOURCE_DIR}/pent_config.h.in"
   "${CMAKE_INSTALL_PREFIX}/include/pent_config.h"
   )
message(STATUS "pent_config.h: ${CMAKE_INSTALL_PREFIX}/include/pent_config.h")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.64.0 REQUIRED COMPONENTS system date_time)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/pent_core")

add_executable(${PROJECT_NAME} pent_config.h main.cpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
add_subdirectory(pent_core)
target_link_libraries(${PROJECT_NAME} pent_core)
add_subdirectory(eosc_commands)
target_link_libraries(${PROJECT_NAME} eosc_commands)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
