add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Checkpoints Checkpoints/*)

source_group("" FILES ${Checkpoints})

add_executable(Checkpoints ${Checkpoints})

target_link_libraries(Checkpoints gtest_main CryptoNoteCore Crypto Serialization Common Logging)

add_custom_target(Basic DEPENDS Checkpoints)

set_property(TARGET Basic Checkpoints PROPERTY FOLDER "Basic")

set_property(TARGET Checkpoints PROPERTY OUTPUT_NAME "Checkpoints")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()