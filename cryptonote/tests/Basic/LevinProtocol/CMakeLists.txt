add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

file(GLOB_RECURSE LevinProtocol LevinProtocol/*)

source_group("" FILES ${LevinProtocol})

add_executable(LevinProtocol ${LevinProtocol})

target_link_libraries(LevinProtocol gtest_main CryptoNoteCore P2p Rpc Serialization System Logging Common Crypto upnpc-static ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS LevinProtocol)

set_property(TARGET Basic LevinProtocol PROPERTY FOLDER "Basic")

set_property(TARGET LevinProtocol PROPERTY OUTPUT_NAME "LevinProtocol")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()