add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ConnectionContext ConnectionContext/*)

source_group("" FILES ${ConnectionContext})

add_executable(ConnectionContext ${ConnectionContext})

target_link_libraries(ConnectionContext gtest_main Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS ConnectionContext)

set_property(TARGET Basic ConnectionContext PROPERTY FOLDER "Basic")

set_property(TARGET ConnectionContext PROPERTY OUTPUT_NAME "ConnectionContext")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()