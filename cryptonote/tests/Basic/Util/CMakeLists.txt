add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Util Util/*)

source_group("" FILES ${Util})

add_executable(Util ${Util})

target_link_libraries(Util gtest_main Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Util)

set_property(TARGET Basic Util PROPERTY FOLDER "Basic")

set_property(TARGET Util PROPERTY OUTPUT_NAME "Util")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()