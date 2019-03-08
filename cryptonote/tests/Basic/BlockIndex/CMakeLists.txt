add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE BlockIndex BlockIndex/*)

source_group("" FILES ${BlockIndex})

add_executable(BlockIndex ${BlockIndex})

target_link_libraries(BlockIndex gtest_main CryptoNoteCore Crypto Serialization Common Logging)

add_custom_target(Basic DEPENDS BlockIndex)

set_property(TARGET Basic BlockIndex PROPERTY FOLDER "Basic")

set_property(TARGET BlockIndex PROPERTY OUTPUT_NAME "BlockIndex")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()