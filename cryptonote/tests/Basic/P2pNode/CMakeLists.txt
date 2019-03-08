add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE P2pNode P2pNode/*)

source_group("" FILES ${P2pNode})

add_executable(P2pNode ${P2pNode})

target_link_libraries(P2pNode gtest_main P2p CryptoNoteCore Crypto Serialization Logging System Common upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS P2pNode)

set_property(TARGET Basic P2pNode PROPERTY FOLDER "Basic")

set_property(TARGET P2pNode PROPERTY OUTPUT_NAME "P2pNode")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()