add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE CryptoNoteFormatUtils CryptoNoteFormatUtils/*)

source_group("" FILES ${CryptoNoteFormatUtils})

add_executable(CryptoNoteFormatUtils ${CryptoNoteFormatUtils})

target_link_libraries(CryptoNoteFormatUtils gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS CryptoNoteFormatUtils)

set_property(TARGET Basic CryptoNoteFormatUtils PROPERTY FOLDER "Basic")

set_property(TARGET CryptoNoteFormatUtils PROPERTY OUTPUT_NAME "CryptoNoteFormatUtils")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()