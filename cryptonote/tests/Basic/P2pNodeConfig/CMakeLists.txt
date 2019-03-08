add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE P2pNodeConfig P2pNodeConfig/*)

source_group("" FILES ${P2pNodeConfig})

add_executable(P2pNodeConfig ${P2pNodeConfig})

target_link_libraries(P2pNodeConfig gtest_main P2p CryptoNoteCore Crypto Serialization Logging System Common upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS P2pNodeConfig)

set_property(TARGET Basic P2pNodeConfig PROPERTY FOLDER "Basic")

set_property(TARGET P2pNodeConfig PROPERTY OUTPUT_NAME "P2pNodeConfig")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()