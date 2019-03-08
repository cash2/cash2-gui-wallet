add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Context Context/*)

source_group("" FILES ${Context})

add_executable(Context ${Context})

target_link_libraries(Context gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Context)

set_property(TARGET Basic Context PROPERTY FOLDER "Basic")

set_property(TARGET Context PROPERTY OUTPUT_NAME "Context")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()