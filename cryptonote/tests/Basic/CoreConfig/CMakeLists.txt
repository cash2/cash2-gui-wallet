add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE CoreConfig CoreConfig/*)

source_group("" FILES ${CoreConfig})

add_executable(CoreConfig ${CoreConfig})

target_link_libraries(CoreConfig gtest_main CryptoNoteCore Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS CoreConfig)

set_property(TARGET Basic CoreConfig PROPERTY FOLDER "Basic")

set_property(TARGET CoreConfig PROPERTY OUTPUT_NAME "CoreConfig")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()