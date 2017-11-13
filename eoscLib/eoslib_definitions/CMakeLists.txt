include_directories(
   "/mnt/hgfs/Workspaces/EOS/eos/contracts"
   )
add_library(print print.cpp)
add_library(message message.cpp)
add_library(system system.cpp)

install(TARGETS print DESTINATION lib)
install(TARGETS message DESTINATION lib)
install(TARGETS system DESTINATION lib)