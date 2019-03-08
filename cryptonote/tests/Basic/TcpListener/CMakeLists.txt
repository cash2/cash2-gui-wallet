add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE TcpListener TcpListener/*)

source_group("" FILES ${TcpListener})

add_executable(TcpListener ${TcpListener})

target_link_libraries(TcpListener gtest_main System)

add_custom_target(Basic DEPENDS TcpListener)

set_property(TARGET Basic TcpListener PROPERTY FOLDER "Basic")

set_property(TARGET TcpListener PROPERTY OUTPUT_NAME "TcpListener")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()