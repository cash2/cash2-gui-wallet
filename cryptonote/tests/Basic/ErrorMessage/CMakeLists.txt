add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE ErrorMessage ErrorMessage/*)

source_group("" FILES ${ErrorMessage})

add_executable(ErrorMessage ${ErrorMessage})

target_link_libraries(ErrorMessage gtest_main System)

add_custom_target(Basic DEPENDS ErrorMessage)

set_property(TARGET Basic ErrorMessage PROPERTY FOLDER "Basic")

set_property(TARGET ErrorMessage PROPERTY OUTPUT_NAME "ErrorMessage")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()