# minimun requirements
# my cmake cmake version 3.14.5
cmake_minimum_required(VERSION 3.9.4)
#project name
project(utils)
# mark the cpp files as sources.
file(GLOB SOURCES "src/*.cpp")

#link_libraries(${Boost_LIB_DIRS})
add_library(utils STATIC ${SOURCES})

include_directories(src/)
include_directories(${Boost_INCLUDE_DIRS})


# google test
include_directories(${GTEST_ROOT})

add_executable( test_utils
                test/main.cpp
                ${GTEST_ROOT}/gtest/gtest-all.cc
                ${GTEST_ROOT}/gmock/gmock-all.cc)
target_link_libraries(  test_utils
                        utils )

