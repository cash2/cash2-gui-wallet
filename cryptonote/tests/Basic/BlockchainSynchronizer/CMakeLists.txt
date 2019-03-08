add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE BlockchainSynchronizer BlockchainSynchronizer/*)

source_group("" FILES ${BlockchainSynchronizer})

add_executable(BlockchainSynchronizer ${BlockchainSynchronizer})

target_link_libraries(BlockchainSynchronizer gtest_main Transfers CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS BlockchainSynchronizer)

set_property(TARGET Basic BlockchainSynchronizer PROPERTY FOLDER "Basic")

set_property(TARGET BlockchainSynchronizer PROPERTY OUTPUT_NAME "BlockchainSynchronizer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()