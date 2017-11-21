include_directories(${Boost_INCLUDE_DIRS})

add_library(pentagon1 STATIC pentagon1.hpp pentagon1.cpp transactions.cpp)

target_link_libraries(pentagon1 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pentagon1 ${Boost_LIBRARIES})

install (TARGETS pentagon1 DESTINATION lib)
install (FILES pentagon1.hpp DESTINATION include)