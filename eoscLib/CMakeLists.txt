cmake_minimum_required (VERSION 3.6)
project (ContractHello)

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
add_subdirectory (eosContract)
include_directories("${PROJECT_SOURCE_DIR}/eoscContract")
include_directories("/mnt/hgfs/Workspaces/EOS/eos/contracts")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} system)
target_link_libraries(${PROJECT_NAME} print)
target_link_libraries(${PROJECT_NAME} message)
target_link_libraries(${PROJECT_NAME} contract)

#### INSTALL
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
