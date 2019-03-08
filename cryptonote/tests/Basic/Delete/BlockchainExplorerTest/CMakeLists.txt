add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests/HelperFunctions)

file(GLOB_RECURSE BlockchainExplorerTests BlockchainExplorerTests/*)

source_group("" FILES ${BlockchainExplorerTests})

add_executable(BlockchainExplorerTests ${BlockchainExplorerTests})

target_link_libraries(BlockchainExplorerTest gtest_main BlockchainExplorer Wallet CryptoNoteCore Crypto Serialization Logging System Common ${Boost_LIBRARIES})

if(NOT MSVC)
  set_property(TARGET gtest gtest_main BlockchainExplorerTests APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-sign-compare -O0")
endif()

add_custom_target(tests DEPENDS BlockchainExplorerTests)

set_property(TARGET
  tests
 
  BlockchainExplorerTests

PROPERTY FOLDER "tests")

set_property(TARGET BlockchainExplorerTests PROPERTY OUTPUT_NAME "BlockchainExplorerTests")

add_test(BlockchainExplorerTests BlockchainExplorerTests)