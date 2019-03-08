add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE SignalHandler SignalHandler/*)

source_group("" FILES ${SignalHandler})

add_executable(SignalHandler ${SignalHandler})

target_link_libraries(SignalHandler gtest_main Common)

add_custom_target(Basic DEPENDS SignalHandler)

set_property(TARGET Basic SignalHandler PROPERTY FOLDER "Basic")

set_property(TARGET SignalHandler PROPERTY OUTPUT_NAME "SignalHandler")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()