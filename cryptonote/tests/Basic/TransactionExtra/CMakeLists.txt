add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransactionExtra TransactionExtra/*)

source_group("" FILES ${TransactionExtra})

add_executable(TransactionExtra ${TransactionExtra})

target_link_libraries(TransactionExtra gtest_main CryptoNoteCore Crypto Serialization Logging Common)

add_custom_target(Basic DEPENDS TransactionExtra)

set_property(TARGET Basic TransactionExtra PROPERTY FOLDER "Basic")

set_property(TARGET TransactionExtra PROPERTY OUTPUT_NAME "TransactionExtra")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()