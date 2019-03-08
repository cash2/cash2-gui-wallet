add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE LoggerManager LoggerManager/*)

source_group("" FILES ${LoggerManager})

add_executable(LoggerManager ${LoggerManager})

target_link_libraries(LoggerManager gtest_main Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS LoggerManager)

set_property(TARGET Basic LoggerManager PROPERTY FOLDER "Basic")

set_property(TARGET LoggerManager PROPERTY OUTPUT_NAME "LoggerManager")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()