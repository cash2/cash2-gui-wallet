add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ParseAmount ParseAmount/*)

source_group("" FILES ${ParseAmount})

add_executable(ParseAmount ${ParseAmount})

target_link_libraries(ParseAmount gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS ParseAmount)

set_property(TARGET Basic ParseAmount PROPERTY FOLDER "Basic")

set_property(TARGET ParseAmount PROPERTY OUTPUT_NAME "ParseAmount")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()