add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests/HelperFunctions)

file(GLOB_RECURSE BlockchainExplorerDataBuilder BlockchainExplorerDataBuilder/*)

source_group("" FILES ${BlockchainExplorerDataBuilder})

add_executable(BlockchainExplorerDataBuilder ${BlockchainExplorerDataBuilder})

target_link_libraries(BlockchainExplorerDataBuilder gtest_main BlockchainExplorer CryptoNoteCore Crypto Serialization Logging System Common ${Boost_LIBRARIES})

if(NOT MSVC)
  set_property(TARGET gtest gtest_main BlockchainExplorerDataBuilder APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-sign-compare -O0")
endif()

add_custom_target(tests DEPENDS BlockchainExplorerDataBuilder)

set_property(TARGET
  tests
 
  BlockchainExplorerDataBuilder

PROPERTY FOLDER "tests")

set_property(TARGET BlockchainExplorerDataBuilder PROPERTY OUTPUT_NAME "blockchainExplorerDataBuilder")

add_test(BlockchainExplorerDataBuilder blockchainExplorerDataBuilder)