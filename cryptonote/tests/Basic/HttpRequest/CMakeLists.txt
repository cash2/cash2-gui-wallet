add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE HttpRequest HttpRequest/*)

source_group("" FILES ${HttpRequest})

add_executable(HttpRequest ${HttpRequest})

target_link_libraries(HttpRequest gtest_main Http)

add_custom_target(Basic DEPENDS HttpRequest)

set_property(TARGET Basic HttpRequest PROPERTY FOLDER "Basic")

set_property(TARGET HttpRequest PROPERTY OUTPUT_NAME "HttpRequest")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()