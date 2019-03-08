add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE TransfersSynchronizer TransfersSynchronizer/*)

source_group("" FILES ${TransfersSynchronizer})

add_executable(TransfersSynchronizer ${TransfersSynchronizer})

target_link_libraries(TransfersSynchronizer gtest_main Transfers CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS TransfersSynchronizer)

set_property(TARGET Basic TransfersSynchronizer PROPERTY FOLDER "Basic")

set_property(TARGET TransfersSynchronizer PROPERTY OUTPUT_NAME "TransfersSynchronizer")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()