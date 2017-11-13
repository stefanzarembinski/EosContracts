cmake_minimum_required (VERSION 3.6)
project (Simplest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(../eosContracts.cmake)

set(CMAKE_BUILD_TYPE Debug)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.64.0 REQUIRED COMPONENTS system log program_options)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED) # boost::asio wants it.

# add the executable
add_executable(${PROJECT_NAME} main.cpp)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# add the install targets: make install
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
