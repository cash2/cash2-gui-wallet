add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE LoggerMessage LoggerMessage/*)

source_group("" FILES ${LoggerMessage})

add_executable(LoggerMessage ${LoggerMessage})

target_link_libraries(LoggerMessage gtest_main Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS LoggerMessage)

set_property(TARGET Basic LoggerMessage PROPERTY FOLDER "Basic")

set_property(TARGET LoggerMessage PROPERTY OUTPUT_NAME "LoggerMessage")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()