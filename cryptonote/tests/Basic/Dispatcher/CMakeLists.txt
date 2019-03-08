add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Dispatcher Dispatcher/*)

source_group("" FILES ${Dispatcher})

add_executable(Dispatcher ${Dispatcher})

target_link_libraries(Dispatcher gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Dispatcher)

set_property(TARGET Basic Dispatcher PROPERTY FOLDER "Basic")

set_property(TARGET Dispatcher PROPERTY OUTPUT_NAME "Dispatcher")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()