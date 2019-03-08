add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE NetNode NetNode/*)

source_group("" FILES ${NetNode})

add_executable(NetNode ${NetNode})

target_link_libraries(NetNode gtest_main P2p CryptoNoteCore BlockchainExplorer Crypto Serialization Logging System Common upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS NetNode)

set_property(TARGET Basic NetNode PROPERTY FOLDER "Basic")

set_property(TARGET NetNode PROPERTY OUTPUT_NAME "NetNode")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()