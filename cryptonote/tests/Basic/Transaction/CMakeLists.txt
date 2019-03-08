add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Transaction Transaction/*)

source_group("" FILES ${Transaction})

add_executable(Transaction ${Transaction})

target_link_libraries(Transaction gtest_main CryptoNoteCore Crypto Serialization Logging Common)

add_custom_target(Basic DEPENDS Transaction)

set_property(TARGET Basic Transaction PROPERTY FOLDER "Basic")

set_property(TARGET Transaction PROPERTY OUTPUT_NAME "Transaction")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()