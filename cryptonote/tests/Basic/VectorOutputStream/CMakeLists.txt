add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE VectorOutputStream VectorOutputStream/*)

source_group("" FILES ${VectorOutputStream})

add_executable(VectorOutputStream ${VectorOutputStream})

target_link_libraries(VectorOutputStream gtest_main Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS VectorOutputStream)

set_property(TARGET Basic VectorOutputStream PROPERTY FOLDER "Basic")

set_property(TARGET VectorOutputStream PROPERTY OUTPUT_NAME "VectorOutputStream")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()