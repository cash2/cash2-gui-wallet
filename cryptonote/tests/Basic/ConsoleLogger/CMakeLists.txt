add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ConsoleLogger ConsoleLogger/*)

source_group("" FILES ${ConsoleLogger})

add_executable(ConsoleLogger ${ConsoleLogger})

target_link_libraries(ConsoleLogger gtest_main Logging Common)

add_custom_target(Basic DEPENDS ConsoleLogger)

set_property(TARGET Basic ConsoleLogger PROPERTY FOLDER "Basic")

set_property(TARGET ConsoleLogger PROPERTY OUTPUT_NAME "ConsoleLogger")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()