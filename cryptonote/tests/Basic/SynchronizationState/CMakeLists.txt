add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE SynchronizationState SynchronizationState/*)

source_group("" FILES ${SynchronizationState})

add_executable(SynchronizationState ${SynchronizationState})

target_link_libraries(SynchronizationState gtest_main Transfers CryptoNoteCore Crypto Serialization Logging Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS SynchronizationState)

set_property(TARGET Basic SynchronizationState PROPERTY FOLDER "Basic")

set_property(TARGET SynchronizationState PROPERTY OUTPUT_NAME "SynchronizationState")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()