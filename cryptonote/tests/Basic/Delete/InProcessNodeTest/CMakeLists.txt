add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests/HelperFunctions)

file(GLOB_RECURSE InProcessNodeTest InProcessNodeTest/*)

source_group("" FILES ${InProcessNodeTest})

add_executable(InProcessNodeTest ${InProcessNodeTest})

target_link_libraries(InProcessNodeTest gtest_main InProcessNode CryptoNoteCore Crypto Serialization Logging BlockchainExplorer System Common ${Boost_LIBRARIES})

if(NOT MSVC)
  set_property(TARGET gtest gtest_main InProcessNodeTest APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-undef -Wno-sign-compare -O0")
endif()

add_custom_target(tests DEPENDS InProcessNodeTest)

set_property(TARGET
  tests
 
  InProcessNodeTest

PROPERTY FOLDER "tests")

set_property(TARGET InProcessNodeTest PROPERTY OUTPUT_NAME "inProcessNodeTest")

add_test(InProcessNodeTest inProcessNodeTest)