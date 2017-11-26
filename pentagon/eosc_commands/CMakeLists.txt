
include_directories("${CMAKE_INSTALL_PREFIX}/include")
include_directories(${Boost_INCLUDE_DIRS})

add_library(eosc_commands STATIC 
  eosc_get_commands.hpp eosc_commands.cpp eosc_get_commands.hpp)

target_link_libraries(eosc_commands ${Boost_LIBRARIES})
target_link_libraries(eosc_commands pent_core)

install (TARGETS eosc_commands DESTINATION lib)
install (FILES eosc_commands.hpp eosc_get_commands.hpp 
  DESTINATION include)