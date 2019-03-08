add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransfersSubscription TransfersSubscription/*)

source_group("" FILES ${TransfersSubscription})

add_executable(TransfersSubscription ${TransfersSubscription})

target_link_libraries(TransfersSubscription gtest_main Transfers CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TransfersSubscription)

set_property(TARGET Basic TransfersSubscription PROPERTY FOLDER "Basic")

set_property(TARGET TransfersSubscription PROPERTY OUTPUT_NAME "TransfersSubscription")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()