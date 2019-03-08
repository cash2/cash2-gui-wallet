add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransactionApiExtra TransactionApiExtra/*)

source_group("" FILES ${TransactionApiExtra})

add_executable(TransactionApiExtra ${TransactionApiExtra})

target_link_libraries(TransactionApiExtra gtest_main CryptoNoteCore Crypto Serialization Logging Common)

add_custom_target(Basic DEPENDS TransactionApiExtra)

set_property(TARGET Basic TransactionApiExtra PROPERTY FOLDER "Basic")

set_property(TARGET TransactionApiExtra PROPERTY OUTPUT_NAME "TransactionApiExtra")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()