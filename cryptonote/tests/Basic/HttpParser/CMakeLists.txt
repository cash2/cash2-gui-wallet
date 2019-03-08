add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE HttpParser HttpParser/*)

source_group("" FILES ${HttpParser})

add_executable(HttpParser ${HttpParser})

target_link_libraries(HttpParser gtest_main Http)

add_custom_target(Basic DEPENDS HttpParser)

set_property(TARGET Basic HttpParser PROPERTY FOLDER "Basic")

set_property(TARGET HttpParser PROPERTY OUTPUT_NAME "HttpParser")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()