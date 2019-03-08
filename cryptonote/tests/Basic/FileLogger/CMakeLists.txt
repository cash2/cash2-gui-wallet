add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE FileLogger FileLogger/*)

source_group("" FILES ${FileLogger})

add_executable(FileLogger ${FileLogger})

target_link_libraries(FileLogger gtest_main Logging Common)

add_custom_target(Basic DEPENDS FileLogger)

set_property(TARGET Basic FileLogger PROPERTY FOLDER "Basic")

set_property(TARGET FileLogger PROPERTY OUTPUT_NAME "FileLogger")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()