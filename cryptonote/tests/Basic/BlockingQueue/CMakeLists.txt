add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE BlockingQueue BlockingQueue/*)

source_group("" FILES ${BlockingQueue})

add_executable(BlockingQueue ${BlockingQueue})

target_link_libraries(BlockingQueue gtest_main Common)

add_custom_target(Basic DEPENDS BlockingQueue)

set_property(TARGET Basic BlockingQueue PROPERTY FOLDER "Basic")

set_property(TARGET BlockingQueue PROPERTY OUTPUT_NAME "BlockingQueue")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()