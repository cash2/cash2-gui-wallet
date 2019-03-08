add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE HttpResponse HttpResponse/*)

source_group("" FILES ${HttpResponse})

add_executable(HttpResponse ${HttpResponse})

target_link_libraries(HttpResponse gtest_main Http)

add_custom_target(Basic DEPENDS HttpResponse)

set_property(TARGET Basic HttpResponse PROPERTY FOLDER "Basic")

set_property(TARGET HttpResponse PROPERTY OUTPUT_NAME "HttpResponse")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()