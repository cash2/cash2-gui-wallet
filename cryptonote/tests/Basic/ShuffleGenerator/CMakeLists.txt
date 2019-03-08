add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ShuffleGenerator ShuffleGenerator/*)

source_group("" FILES ${ShuffleGenerator})

add_executable(ShuffleGenerator ${ShuffleGenerator})

target_link_libraries(ShuffleGenerator gtest_main Common)

add_custom_target(Basic DEPENDS ShuffleGenerator)

set_property(TARGET Basic ShuffleGenerator PROPERTY FOLDER "Basic")

set_property(TARGET ShuffleGenerator PROPERTY OUTPUT_NAME "ShuffleGenerator")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()