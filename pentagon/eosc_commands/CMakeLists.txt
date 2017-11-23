
include_directories("${CMAKE_INSTALL_PREFIX}/include")
add_library(eosc_commands STATIC eosc_commands.hpp eosc_commands.cpp)

install (TARGETS eosc_commands DESTINATION lib)
install (FILES eosc_commands.hpp DESTINATION include)