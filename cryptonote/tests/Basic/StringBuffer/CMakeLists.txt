add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE StringBuffer StringBuffer/*)

source_group("" FILES ${StringBuffer})

add_executable(StringBuffer ${StringBuffer})

target_link_libraries(StringBuffer gtest_main Common)

add_custom_target(Basic DEPENDS StringBuffer)

set_property(TARGET Basic StringBuffer PROPERTY FOLDER "Basic")

set_property(TARGET StringBuffer PROPERTY OUTPUT_NAME "StringBuffer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()