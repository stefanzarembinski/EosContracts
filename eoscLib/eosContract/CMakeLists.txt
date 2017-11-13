include_directories(
   "/mnt/hgfs/Workspaces/EOS/eos/contracts"
   )
add_library(contract contract.cpp)
target_link_libraries(contract 
   "${PROJECT_BINARY_DIR}/eoslib_definitions/libsystem.a"
   "${PROJECT_BINARY_DIR}/eoslib_definitions/libprint.a"
   "${PROJECT_BINARY_DIR}/eoslib_definitions/libmessage.a"
   )

install(TARGETS contract DESTINATION lib)
install(FILES contract.hpp DESTINATION include)