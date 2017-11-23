include_directories("${CMAKE_INSTALL_PREFIX}/include")
include_directories(${Boost_INCLUDE_DIRS})

add_library(pent_core STATIC pent_core.hpp pent_core.cpp transactions.cpp)

target_link_libraries(pent_core ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pent_core ${Boost_LIBRARIES})

install (TARGETS pent_core DESTINATION lib)
install (FILES pent_core.hpp DESTINATION include)