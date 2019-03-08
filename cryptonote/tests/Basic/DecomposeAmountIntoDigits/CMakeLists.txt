add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE DecomposeAmountIntoDigits DecomposeAmountIntoDigits/*)

source_group("" FILES ${DecomposeAmountIntoDigits})

add_executable(DecomposeAmountIntoDigits ${DecomposeAmountIntoDigits})

target_link_libraries(DecomposeAmountIntoDigits gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS DecomposeAmountIntoDigits)

set_property(TARGET Basic DecomposeAmountIntoDigits PROPERTY FOLDER "Basic")

set_property(TARGET DecomposeAmountIntoDigits PROPERTY OUTPUT_NAME "DecomposeAmountIntoDigits")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()