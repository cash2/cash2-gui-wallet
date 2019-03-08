add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransfersContainer TransfersContainer/*)

source_group("" FILES ${TransfersContainer})

add_executable(TransfersContainer ${TransfersContainer})

target_link_libraries(TransfersContainer gtest_main CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TransfersContainer)

set_property(TARGET Basic TransfersContainer PROPERTY FOLDER "Basic")

set_property(TARGET TransfersContainer PROPERTY OUTPUT_NAME "TransfersContainer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()