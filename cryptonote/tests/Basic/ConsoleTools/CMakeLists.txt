add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ConsoleTools ConsoleTools/*)

source_group("" FILES ${ConsoleTools})

add_executable(ConsoleTools ${ConsoleTools})

target_link_libraries(ConsoleTools gtest_main Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS ConsoleTools)

set_property(TARGET Basic ConsoleTools PROPERTY FOLDER "Basic")

set_property(TARGET ConsoleTools PROPERTY OUTPUT_NAME "ConsoleTools")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()