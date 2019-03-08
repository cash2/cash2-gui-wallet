add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE EventLock EventLock/*)

source_group("" FILES ${EventLock})

add_executable(EventLock ${EventLock})

target_link_libraries(EventLock gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS EventLock)

set_property(TARGET Basic EventLock PROPERTY FOLDER "Basic")

set_property(TARGET EventLock PROPERTY OUTPUT_NAME "EventLock")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()