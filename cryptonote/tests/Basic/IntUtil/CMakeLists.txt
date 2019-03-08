add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE IntUtil IntUtil/*)

source_group("" FILES ${IntUtil})

add_executable(IntUtil ${IntUtil})

target_link_libraries(IntUtil gtest_main Common)

add_custom_target(Basic DEPENDS IntUtil)

set_property(TARGET Basic IntUtil PROPERTY FOLDER "Basic")

set_property(TARGET IntUtil PROPERTY OUTPUT_NAME "IntUtil")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()