add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ContextGroupTimeout ContextGroupTimeout/*)

source_group("" FILES ${ContextGroupTimeout})

add_executable(ContextGroupTimeout ${ContextGroupTimeout})

target_link_libraries(ContextGroupTimeout gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS ContextGroupTimeout)

set_property(TARGET Basic ContextGroupTimeout PROPERTY FOLDER "Basic")

set_property(TARGET ContextGroupTimeout PROPERTY OUTPUT_NAME "ContextGroupTimeout")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()