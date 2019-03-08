add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE StreamLogger StreamLogger/*)

source_group("" FILES ${StreamLogger})

add_executable(StreamLogger ${StreamLogger})

target_link_libraries(StreamLogger gtest_main Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS StreamLogger)

set_property(TARGET Basic StreamLogger PROPERTY FOLDER "Basic")

set_property(TARGET StreamLogger PROPERTY OUTPUT_NAME "StreamLogger")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()