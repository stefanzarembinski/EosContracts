include_directories(${Boost_INCLUDE_DIRS})
add_library(transactions STATIC transactions.cpp, transactions.hpp)
target_link_libraries(transactions ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(transactions ${Boost_LIBRARIES})

#install (TARGETS transactions LIBRARY DESTINATION lib)
#install (FILES "transactions.hpp" DESTINATION include)