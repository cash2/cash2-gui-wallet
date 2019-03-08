add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ContextGroup ContextGroup/*)

source_group("" FILES ${ContextGroup})

add_executable(ContextGroup ${ContextGroup})

target_link_libraries(ContextGroup gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS ContextGroup)

set_property(TARGET Basic ContextGroup PROPERTY FOLDER "Basic")

set_property(TARGET ContextGroup PROPERTY OUTPUT_NAME "ContextGroup")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()