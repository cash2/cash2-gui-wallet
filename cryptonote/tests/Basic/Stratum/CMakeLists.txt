add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Stratum Stratum/*)

source_group("" FILES ${Stratum})

add_executable(Stratum ${Stratum})

target_link_libraries(Stratum gtest_main CryptoNoteCore Crypto Serialization Logging System Common upnpc-static P2p ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Stratum)

set_property(TARGET Basic Stratum PROPERTY FOLDER "Basic")

set_property(TARGET Stratum PROPERTY OUTPUT_NAME "Stratum")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()