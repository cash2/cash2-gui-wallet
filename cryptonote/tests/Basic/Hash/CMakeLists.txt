add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Hash Hash/*)

source_group("" FILES ${Hash})

add_executable(Hash ${Hash})

target_link_libraries(Hash gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS Hash)

set_property(TARGET Basic Hash PROPERTY FOLDER "Basic")

set_property(TARGET Hash PROPERTY OUTPUT_NAME "Hash")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()