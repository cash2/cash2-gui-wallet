add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Ipv4Resolver Ipv4Resolver/*)

source_group("" FILES ${Ipv4Resolver})

add_executable(Ipv4Resolver ${Ipv4Resolver})

target_link_libraries(Ipv4Resolver gtest_main System)

add_custom_target(Basic DEPENDS Ipv4Resolver)

set_property(TARGET Basic Ipv4Resolver PROPERTY FOLDER "Basic")

set_property(TARGET Ipv4Resolver PROPERTY OUTPUT_NAME "Ipv4Resolver")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()