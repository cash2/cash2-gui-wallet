add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE BlockchainIndexes BlockchainIndexes/*)

source_group("" FILES ${BlockchainIndexes})

add_executable(BlockchainIndexes ${BlockchainIndexes})

target_link_libraries(BlockchainIndexes gtest_main CryptoNoteCore BlockchainExplorer Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS BlockchainIndexes)

set_property(TARGET Basic BlockchainIndexes PROPERTY FOLDER "Basic")

set_property(TARGET BlockchainIndexes PROPERTY OUTPUT_NAME "BlockchainIndexes")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()