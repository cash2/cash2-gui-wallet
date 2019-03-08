add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE CryptoNoteBasicImpl CryptoNoteBasicImpl/*)

source_group("" FILES ${CryptoNoteBasicImpl})

add_executable(CryptoNoteBasicImpl ${CryptoNoteBasicImpl})

target_link_libraries(CryptoNoteBasicImpl gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS CryptoNoteBasicImpl)

set_property(TARGET Basic CryptoNoteBasicImpl PROPERTY FOLDER "Basic")

set_property(TARGET CryptoNoteBasicImpl PROPERTY OUTPUT_NAME "CryptoNoteBasicImpl")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()