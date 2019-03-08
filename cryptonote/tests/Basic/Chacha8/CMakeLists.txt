add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Chacha8 Chacha8/*)

source_group("" FILES ${Chacha8})

add_executable(Chacha8 ${Chacha8})

target_link_libraries(Chacha8 gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS Chacha8)

set_property(TARGET Basic Chacha8 PROPERTY FOLDER "Basic")

set_property(TARGET Chacha8 PROPERTY OUTPUT_NAME "Chacha8")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()