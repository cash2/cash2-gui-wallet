add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Timer Timer/*)

source_group("" FILES ${Timer})

add_executable(Timer ${Timer})

target_link_libraries(Timer gtest_main System)

add_custom_target(Basic DEPENDS Timer)

set_property(TARGET Basic Timer PROPERTY FOLDER "Basic")

set_property(TARGET Timer PROPERTY OUTPUT_NAME "Timer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()