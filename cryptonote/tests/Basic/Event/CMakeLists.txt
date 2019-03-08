add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Event Event/*)

source_group("" FILES ${Event})

add_executable(Event ${Event})

target_link_libraries(Event gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Event)

set_property(TARGET Basic Event PROPERTY FOLDER "Basic")

set_property(TARGET Event PROPERTY OUTPUT_NAME "Event")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()