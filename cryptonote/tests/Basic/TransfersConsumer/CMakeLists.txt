add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransfersConsumer TransfersConsumer/*)

source_group("" FILES ${TransfersConsumer})

add_executable(TransfersConsumer ${TransfersConsumer})

target_link_libraries(TransfersConsumer gtest_main Transfers CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TransfersConsumer)

set_property(TARGET Basic TransfersConsumer PROPERTY FOLDER "Basic")

set_property(TARGET TransfersConsumer PROPERTY OUTPUT_NAME "TransfersConsumer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()