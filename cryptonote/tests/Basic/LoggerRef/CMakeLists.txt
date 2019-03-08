add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE LoggerRef LoggerRef/*)

source_group("" FILES ${LoggerRef})

add_executable(LoggerRef ${LoggerRef})

target_link_libraries(LoggerRef gtest_main Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS LoggerRef)

set_property(TARGET Basic LoggerRef PROPERTY FOLDER "Basic")

set_property(TARGET LoggerRef PROPERTY OUTPUT_NAME "LoggerRef")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()