add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE Address Address/*)

source_group("" FILES ${Address})

add_executable(Address ${Address})

target_link_libraries(Address gtest_main CryptoNoteCore Crypto Common Serialization Logging)

add_custom_target(Basic DEPENDS Address)

set_property(TARGET Basic Address PROPERTY FOLDER "Basic")

set_property(TARGET Address PROPERTY OUTPUT_NAME "Address")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()