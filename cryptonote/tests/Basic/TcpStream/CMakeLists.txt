add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE TcpStream TcpStream/*)

source_group("" FILES ${TcpStream})

add_executable(TcpStream ${TcpStream})

target_link_libraries(TcpStream gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TcpStream)

set_property(TARGET Basic TcpStream PROPERTY FOLDER "Basic")

set_property(TARGET TcpStream PROPERTY OUTPUT_NAME "TcpStream")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()