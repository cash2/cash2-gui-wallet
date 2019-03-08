add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE BlockchainMessages BlockchainMessages/*)

source_group("" FILES ${BlockchainMessages})

add_executable(BlockchainMessages ${BlockchainMessages})

target_link_libraries(BlockchainMessages gtest_main CryptoNoteCore Crypto Serialization Common Logging)

add_custom_target(Basic DEPENDS BlockchainMessages)

set_property(TARGET Basic BlockchainMessages PROPERTY FOLDER "Basic")

set_property(TARGET BlockchainMessages PROPERTY OUTPUT_NAME "BlockchainMessages")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()