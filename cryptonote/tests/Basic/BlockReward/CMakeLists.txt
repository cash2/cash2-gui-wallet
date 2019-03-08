add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE BlockReward BlockReward/*)

source_group("" FILES ${BlockReward})

add_executable(BlockReward ${BlockReward})

target_link_libraries(BlockReward gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS BlockReward)

set_property(TARGET Basic BlockReward PROPERTY FOLDER "Basic")

set_property(TARGET BlockReward PROPERTY OUTPUT_NAME "BlockReward")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()