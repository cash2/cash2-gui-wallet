add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE InterruptedException InterruptedException/*)

source_group("" FILES ${InterruptedException})

add_executable(InterruptedException ${InterruptedException})

target_link_libraries(InterruptedException gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS InterruptedException)

set_property(TARGET Basic InterruptedException PROPERTY FOLDER "Basic")

set_property(TARGET InterruptedException PROPERTY OUTPUT_NAME "InterruptedException")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()