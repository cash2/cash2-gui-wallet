add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE JsonValue JsonValue/*)

source_group("" FILES ${JsonValue})

add_executable(JsonValue ${JsonValue})

target_link_libraries(JsonValue gtest_main Common System)

add_custom_target(Basic DEPENDS JsonValue)

set_property(TARGET Basic JsonValue PROPERTY FOLDER "Basic")

set_property(TARGET JsonValue PROPERTY OUTPUT_NAME "JsonValue")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()