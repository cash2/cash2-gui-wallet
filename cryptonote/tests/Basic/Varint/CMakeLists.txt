add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Varint Varint/*)

source_group("" FILES ${Varint})

add_executable(Varint ${Varint})

target_link_libraries(Varint gtest_main Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Varint)

set_property(TARGET Basic Varint PROPERTY FOLDER "Basic")

set_property(TARGET Varint PROPERTY OUTPUT_NAME "Varint")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()