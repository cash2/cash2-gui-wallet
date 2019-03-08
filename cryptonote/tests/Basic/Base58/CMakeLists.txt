add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Base58 Base58/*)

source_group("" FILES ${Base58})

add_executable(Base58 ${Base58})

target_link_libraries(Base58 gtest_main Common CryptoNoteCore Crypto Serialization Logging)

add_custom_target(Basic DEPENDS Base58)

set_property(TARGET Basic Base58 PROPERTY FOLDER "Basic")

set_property(TARGET Base58 PROPERTY OUTPUT_NAME "Base58")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()