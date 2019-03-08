add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE P2pContextOwner P2pContextOwner/*)

source_group("" FILES ${P2pContextOwner})

add_executable(P2pContextOwner ${P2pContextOwner})

target_link_libraries(P2pContextOwner gtest_main P2p CryptoNoteCore Crypto Serialization Logging System Common upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS P2pContextOwner)

set_property(TARGET Basic P2pContextOwner PROPERTY FOLDER "Basic")

set_property(TARGET P2pContextOwner PROPERTY OUTPUT_NAME "P2pContextOwner")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()