add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE StringTools StringTools/*)

source_group("" FILES ${StringTools})

add_executable(StringTools ${StringTools})

target_link_libraries(StringTools gtest_main Common)

add_custom_target(Basic DEPENDS StringTools)

set_property(TARGET Basic StringTools PROPERTY FOLDER "Basic")

set_property(TARGET StringTools PROPERTY OUTPUT_NAME "StringTools")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()