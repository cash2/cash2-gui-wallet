add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE MessageQueue MessageQueue/*)

source_group("" FILES ${MessageQueue})

add_executable(MessageQueue ${MessageQueue})

target_link_libraries(MessageQueue gtest_main CryptoNoteCore System Crypto Serialization Logging Common)

add_custom_target(Basic DEPENDS MessageQueue)

set_property(TARGET Basic MessageQueue PROPERTY FOLDER "Basic")

set_property(TARGET MessageQueue PROPERTY OUTPUT_NAME "MessageQueue")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()