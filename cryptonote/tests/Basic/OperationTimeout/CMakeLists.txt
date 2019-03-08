add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE OperationTimeout OperationTimeout/*)

source_group("" FILES ${OperationTimeout})

add_executable(OperationTimeout ${OperationTimeout})

target_link_libraries(OperationTimeout gtest_main P2p Serialization System Logging Common Crypto ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS OperationTimeout)

set_property(TARGET Basic OperationTimeout PROPERTY FOLDER "Basic")

set_property(TARGET OperationTimeout PROPERTY OUTPUT_NAME "OperationTimeout")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()