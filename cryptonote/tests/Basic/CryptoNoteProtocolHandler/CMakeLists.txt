add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE CryptoNoteProtocolHandler CryptoNoteProtocolHandler/*)

source_group("" FILES ${CryptoNoteProtocolHandler})

add_executable(CryptoNoteProtocolHandler ${CryptoNoteProtocolHandler})

target_link_libraries(CryptoNoteProtocolHandler gtest_main CryptoNoteCore BlockchainExplorer Crypto Serialization Logging System Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS CryptoNoteProtocolHandler)

set_property(TARGET Basic CryptoNoteProtocolHandler PROPERTY FOLDER "Basic")

set_property(TARGET CryptoNoteProtocolHandler PROPERTY OUTPUT_NAME "CryptoNoteProtocolHandler")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()