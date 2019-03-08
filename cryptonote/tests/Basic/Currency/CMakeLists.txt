add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Currency Currency/*)

source_group("" FILES ${Currency})

add_executable(Currency ${Currency})

target_link_libraries(Currency gtest_main CryptoNoteCore Serialization Common Crypto Logging)

add_custom_target(Basic DEPENDS Currency)

set_property(TARGET Basic Currency PROPERTY FOLDER "Basic")

set_property(TARGET Currency PROPERTY OUTPUT_NAME "Currency")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()