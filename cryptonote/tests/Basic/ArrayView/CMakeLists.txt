add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ArrayView ArrayView/*)

source_group("" FILES ${ArrayView})

add_executable(ArrayView ${ArrayView})

target_link_libraries(ArrayView gtest_main Common)

add_custom_target(Basic DEPENDS ArrayView)

set_property(TARGET Basic ArrayView PROPERTY FOLDER "Basic")

set_property(TARGET ArrayView PROPERTY OUTPUT_NAME "ArrayView")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()