add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE CryptoNoteBasic CryptoNoteBasic/*)

source_group("" FILES ${CryptoNoteBasic})

add_executable(CryptoNoteBasic ${CryptoNoteBasic})

target_link_libraries(CryptoNoteBasic gtest_main CryptoNoteCore Crypto Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS CryptoNoteBasic)

set_property(TARGET Basic CryptoNoteBasic PROPERTY FOLDER "Basic")

set_property(TARGET CryptoNoteBasic PROPERTY OUTPUT_NAME "CryptoNoteBasic")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()