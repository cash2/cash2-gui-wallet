add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE TestWallet TestWallet/*)

source_group("" FILES ${TestWallet})

add_executable(TestWallet ${TestWallet})

target_link_libraries(TestWallet gtest_main Wallet InProcessNode NodeRpcProxy Rpc Http Transfers System BlockchainExplorer CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

if(NOT MSVC)
  set_property(TARGET gtest gtest_main TestWallet APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-sign-compare -O0")
endif()

add_custom_target(tests DEPENDS TestWallet)

set_property(TARGET
  tests
 
  TestWallet

PROPERTY FOLDER "tests")

set_property(TARGET TestWallet PROPERTY OUTPUT_NAME "testWallet")

add_test(TestWallet testWallet)