add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ScopeExit ScopeExit/*)

source_group("" FILES ${ScopeExit})

add_executable(ScopeExit ${ScopeExit})

target_link_libraries(ScopeExit gtest_main Common)

add_custom_target(Basic DEPENDS ScopeExit)

set_property(TARGET Basic ScopeExit PROPERTY FOLDER "Basic")

set_property(TARGET ScopeExit PROPERTY OUTPUT_NAME "ScopeExit")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()