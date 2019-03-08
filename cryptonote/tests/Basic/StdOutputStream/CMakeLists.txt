add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE StdOutputStream StdOutputStream/*)

source_group("" FILES ${StdOutputStream})

add_executable(StdOutputStream ${StdOutputStream})

target_link_libraries(StdOutputStream gtest_main Common)

add_custom_target(Basic DEPENDS StdOutputStream)

set_property(TARGET Basic StdOutputStream PROPERTY FOLDER "Basic")

set_property(TARGET StdOutputStream PROPERTY OUTPUT_NAME "StdOutputStream")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()