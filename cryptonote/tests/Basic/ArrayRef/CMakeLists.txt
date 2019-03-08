add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ArrayRef ArrayRef/*)

source_group("" FILES ${ArrayRef})

add_executable(ArrayRef ${ArrayRef})

target_link_libraries(ArrayRef gtest_main Common)

add_custom_target(Basic DEPENDS ArrayRef)

set_property(TARGET Basic ArrayRef PROPERTY FOLDER "Basic")

set_property(TARGET ArrayRef PROPERTY OUTPUT_NAME "ArrayRef")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()