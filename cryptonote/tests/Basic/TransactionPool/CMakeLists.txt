add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransactionPool TransactionPool/*)

source_group("" FILES ${TransactionPool})

add_executable(TransactionPool ${TransactionPool})

target_link_libraries(TransactionPool gtest_main CryptoNoteCore Crypto Serialization Logging BlockchainExplorer Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TransactionPool)

set_property(TARGET Basic TransactionPool PROPERTY FOLDER "Basic")

set_property(TARGET TransactionPool PROPERTY OUTPUT_NAME "TransactionPool")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()