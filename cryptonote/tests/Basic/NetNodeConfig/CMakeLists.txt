add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE NetNodeConfig NetNodeConfig/*)

source_group("" FILES ${NetNodeConfig})

add_executable(NetNodeConfig ${NetNodeConfig})

target_link_libraries(NetNodeConfig gtest_main P2p CryptoNoteCore Crypto Serialization Logging System Common upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS NetNodeConfig)

set_property(TARGET Basic NetNodeConfig PROPERTY FOLDER "Basic")

set_property(TARGET NetNodeConfig PROPERTY OUTPUT_NAME "NetNodeConfig")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()