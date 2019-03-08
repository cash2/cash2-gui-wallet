add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE StringView StringView/*)

source_group("" FILES ${StringView})

add_executable(StringView ${StringView})

target_link_libraries(StringView gtest_main Common)

add_custom_target(Basic DEPENDS StringView)

set_property(TARGET Basic StringView PROPERTY FOLDER "Basic")

set_property(TARGET StringView PROPERTY OUTPUT_NAME "StringView")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()