add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE BlockchainExplorerTest BlockchainExplorerTest/*)

source_group("" FILES ${BlockchainExplorerTest})

add_executable(BlockchainExplorerTest ${BlockchainExplorerTest})

target_link_libraries(BlockchainExplorerTest gtest_main BlockchainExplorer Wallet CryptoNoteCore Crypto Serialization Logging System Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS BlockchainExplorerTest)

set_property(TARGET Basic BlockchainExplorerTest PROPERTY FOLDER "Basic")

set_property(TARGET BlockchainExplorerTest PROPERTY OUTPUT_NAME "BlockchainExplorerTest")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()