add_definitions(-DSTATICLIB)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../version)

include_directories(${CMAKE_SOURCE_DIR}/tests/Basic/HelperFunctions)

file(GLOB_RECURSE Core Core/*)

source_group("" FILES ${Core})

add_executable(Core ${Core})

target_link_libraries(Core gtest_main CryptoNoteCore BlockchainExplorer Crypto Serialization Logging System Common ${Boost_LIBRARIES})

add_custom_target(Basic DEPENDS Core)

set_property(TARGET Basic Core PROPERTY FOLDER "Basic")

set_property(TARGET Core PROPERTY OUTPUT_NAME "Core")

if(NOT MSVC)
  # suppress warnings from gtest
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-sign-compare -O0")
endif()