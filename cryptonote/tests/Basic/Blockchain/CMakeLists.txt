add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Blockchain Blockchain/*)

source_group("" FILES ${Blockchain})

add_executable(Blockchain ${Blockchain})

target_link_libraries(Blockchain gtest_main CryptoNoteCore Crypto Serialization Logging BlockchainExplorer System Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Blockchain)

set_property(TARGET Basic Blockchain PROPERTY FOLDER "Basic")

set_property(TARGET Blockchain PROPERTY OUTPUT_NAME "Blockchain")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()