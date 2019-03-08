add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE TransactionPool TransactionPool/*)

source_group("" FILES ${TransactionPool})

add_executable(TransactionPool ${TransactionPool})

target_link_libraries(TransactionPool gtest_main Wallet InProcessNode NodeRpcProxy Rpc Http Transfers System BlockchainExplorer CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

if(NOT MSVC)
  set_property(TARGET gtest gtest_main TransactionPool APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-sign-compare -O0")
endif()

add_custom_target(tests DEPENDS TransactionPool)

set_property(TARGET
  tests
 
  TransactionPool

PROPERTY FOLDER "tests")

set_property(TARGET TransactionPool PROPERTY OUTPUT_NAME "transactionPool")

add_test(TransactionPool transactionPool)