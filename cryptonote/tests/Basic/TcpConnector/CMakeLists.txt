add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE TcpConnector TcpConnector/*)

source_group("" FILES ${TcpConnector})

add_executable(TcpConnector ${TcpConnector})

target_link_libraries(TcpConnector gtest_main System)

add_custom_target(Basic DEPENDS TcpConnector)

set_property(TARGET Basic TcpConnector PROPERTY FOLDER "Basic")

set_property(TARGET TcpConnector PROPERTY OUTPUT_NAME "TcpConnector")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()