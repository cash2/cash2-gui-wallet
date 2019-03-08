add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE P2pConnectionProxy P2pConnectionProxy/*)

source_group("" FILES ${P2pConnectionProxy})

add_executable(P2pConnectionProxy ${P2pConnectionProxy})

target_link_libraries(P2pConnectionProxy gtest_main P2p CryptoNoteCore Crypto Serialization Logging System Common upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS P2pConnectionProxy)

set_property(TARGET Basic P2pConnectionProxy PROPERTY FOLDER "Basic")

set_property(TARGET P2pConnectionProxy PROPERTY OUTPUT_NAME "P2pConnectionProxy")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()