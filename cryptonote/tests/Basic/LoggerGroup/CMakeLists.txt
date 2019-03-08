add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE LoggerGroup LoggerGroup/*)

source_group("" FILES ${LoggerGroup})

add_executable(LoggerGroup ${LoggerGroup})

target_link_libraries(LoggerGroup gtest_main Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS LoggerGroup)

set_property(TARGET Basic LoggerGroup PROPERTY FOLDER "Basic")

set_property(TARGET LoggerGroup PROPERTY OUTPUT_NAME "LoggerGroup")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()