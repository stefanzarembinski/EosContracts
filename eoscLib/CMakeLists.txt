cmake_minimum_required (VERSION 3.6)
project (EosLib)
include(../config.cmake)

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
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#### FIND DEPENDENCIES ####

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.64.0 REQUIRED COMPONENTS program_options)

#### DEFINE TARGET ####

include_directories(${Boost_INCLUDE_DIRS})
add_subdirectory (eoslib_definitions)
include_directories ("${PROJECT_SOURCE_DIR}/eoslib_definitions")
include_directories("${EOSIO_INSTALL_DIR}//contracts")

