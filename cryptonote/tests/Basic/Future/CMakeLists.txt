add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Future Future/*)

source_group("" FILES ${Future})

add_executable(Future ${Future})

target_link_libraries(Future gtest_main System)

add_custom_target(Basic DEPENDS Future)

set_property(TARGET Basic Future PROPERTY FOLDER "Basic")

set_property(TARGET Future PROPERTY OUTPUT_NAME "Future")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()