add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Ipv4Address Ipv4Address/*)

source_group("" FILES ${Ipv4Address})

add_executable(Ipv4Address ${Ipv4Address})

target_link_libraries(Ipv4Address gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Ipv4Address)

set_property(TARGET Basic Ipv4Address PROPERTY FOLDER "Basic")

set_property(TARGET Ipv4Address PROPERTY OUTPUT_NAME "Ipv4Address")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()