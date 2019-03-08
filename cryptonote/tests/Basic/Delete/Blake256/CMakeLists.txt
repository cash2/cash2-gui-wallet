add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB_RECURSE Blake256 Blake256/*)

source_group("" FILES ${Blake256})

add_executable(Blake256 ${Blake256})

target_link_libraries(Blake256 gtest_main Crypto)

if(NOT MSVC)
  set_property(TARGET gtest gtest_main Blake256 APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-sign-compare -O0")
endif()

add_custom_target(tests DEPENDS Blake256)

set_property(TARGET
  tests
 
  Blake256

PROPERTY FOLDER "tests")

set_property(TARGET Blake256 PROPERTY OUTPUT_NAME "blake256")

add_test(Blake256 blake256)