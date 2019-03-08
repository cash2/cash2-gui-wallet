add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Account Account/*)

source_group("" FILES ${Account})

add_executable(Account ${Account})

target_link_libraries(Account gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS Account)

set_property(TARGET Basic Account PROPERTY FOLDER "Basic")

set_property(TARGET Account PROPERTY OUTPUT_NAME "Account")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()