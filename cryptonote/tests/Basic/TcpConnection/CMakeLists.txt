add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE TcpConnection TcpConnection/*)

source_group("" FILES ${TcpConnection})

add_executable(TcpConnection ${TcpConnection})

target_link_libraries(TcpConnection gtest_main System)

add_custom_target(Basic DEPENDS TcpConnection)

set_property(TARGET Basic TcpConnection PROPERTY FOLDER "Basic")

set_property(TARGET TcpConnection PROPERTY OUTPUT_NAME "TcpConnection")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()