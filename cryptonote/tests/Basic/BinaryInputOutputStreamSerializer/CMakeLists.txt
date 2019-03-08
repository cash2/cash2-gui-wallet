add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE BinaryInputOutputStreamSerializer BinaryInputOutputStreamSerializer/*)

source_group("" FILES ${BinaryInputOutputStreamSerializer})

add_executable(BinaryInputOutputStreamSerializer ${BinaryInputOutputStreamSerializer})

target_link_libraries(BinaryInputOutputStreamSerializer gtest_main Serialization Common)

add_custom_target(Basic DEPENDS BinaryInputOutputStreamSerializer)

set_property(TARGET Basic BinaryInputOutputStreamSerializer PROPERTY FOLDER "Basic")

set_property(TARGET BinaryInputOutputStreamSerializer PROPERTY OUTPUT_NAME "BinaryInputOutputStreamSerializer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()