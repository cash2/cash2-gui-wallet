add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE PathTools PathTools/*)

source_group("" FILES ${PathTools})

add_executable(PathTools ${PathTools})

target_link_libraries(PathTools gtest_main Common)

add_custom_target(Basic DEPENDS PathTools)

set_property(TARGET Basic PathTools PROPERTY FOLDER "Basic")

set_property(TARGET PathTools PROPERTY OUTPUT_NAME "PathTools")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()