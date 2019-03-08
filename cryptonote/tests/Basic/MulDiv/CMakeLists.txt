add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE MulDiv MulDiv/*)

source_group("" FILES ${MulDiv})

add_executable(MulDiv ${MulDiv})

target_link_libraries(MulDiv gtest_main Common)

add_custom_target(Basic DEPENDS MulDiv)

set_property(TARGET Basic MulDiv PROPERTY FOLDER "Basic")

set_property(TARGET MulDiv PROPERTY OUTPUT_NAME "MulDiv")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()