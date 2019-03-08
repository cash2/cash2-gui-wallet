add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE CryptoNoteTools CryptoNoteTools/*)

source_group("" FILES ${CryptoNoteTools})

add_executable(CryptoNoteTools ${CryptoNoteTools})

target_link_libraries(CryptoNoteTools gtest_main CryptoNoteCore Serialization Common Crypto Logging)

add_custom_target(Basic DEPENDS CryptoNoteTools)

set_property(TARGET Basic CryptoNoteTools PROPERTY FOLDER "Basic")

set_property(TARGET CryptoNoteTools PROPERTY OUTPUT_NAME "CryptoNoteTools")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()