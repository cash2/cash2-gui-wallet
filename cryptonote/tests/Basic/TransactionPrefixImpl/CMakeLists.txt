add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransactionPrefixImpl TransactionPrefixImpl/*)

source_group("" FILES ${TransactionPrefixImpl})

add_executable(TransactionPrefixImpl ${TransactionPrefixImpl})

target_link_libraries(TransactionPrefixImpl gtest_main CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TransactionPrefixImpl)

set_property(TARGET Basic TransactionPrefixImpl PROPERTY FOLDER "Basic")

set_property(TARGET TransactionPrefixImpl PROPERTY OUTPUT_NAME "TransactionPrefixImpl")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()