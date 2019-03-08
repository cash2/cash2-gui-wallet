add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE MemoryInputStream MemoryInputStream/*)

source_group("" FILES ${MemoryInputStream})

add_executable(MemoryInputStream ${MemoryInputStream})

target_link_libraries(MemoryInputStream gtest_main Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS MemoryInputStream)

set_property(TARGET Basic MemoryInputStream PROPERTY FOLDER "Basic")

set_property(TARGET MemoryInputStream PROPERTY OUTPUT_NAME "MemoryInputStream")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()