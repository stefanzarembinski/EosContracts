message(STATUS "includes eosContract.cmake")
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../install")
set(EOSIO_INSTALL_DIR "/mnt/hgfs/Workspaces/EOS/eos")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
