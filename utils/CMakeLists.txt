cmake_minimum_required (VERSION 3.6)
project (EosUtils)

include(../eosContracts.cmake)
set(CMAKE_BUILD_TYPE Debug)

# The version number.
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
   "${PROJECT_SOURCE_DIR}/config.h.in"
   "${PROJECT_BINARY_DIR}/config.h"
   )
# add the binary tree to the search path for include files
# so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}") 

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.64.0 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED) # boost::asio wants it.
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(transactions)
include_directories("${PROJECT_SOURCE_DIR}/transactions")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} transactions)

# add the install targets: make install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
