add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE ObserverManager ObserverManager/*)

source_group("" FILES ${ObserverManager})

add_executable(ObserverManager ${ObserverManager})

target_link_libraries(ObserverManager gtest_main Common)

add_custom_target(Basic DEPENDS ObserverManager)

set_property(TARGET Basic ObserverManager PROPERTY FOLDER "Basic")

set_property(TARGET ObserverManager PROPERTY OUTPUT_NAME "ObserverManager")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()