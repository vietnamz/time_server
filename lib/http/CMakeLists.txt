# minimun requirements
# my cmake cmake version 3.14.5
cmake_minimum_required(VERSION 3.9.4)
#project name
project(http)
# mark the cpp files as sources.
file(GLOB SOURCES "src/*.cpp")


include_directories(../util/src)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIB_DIRS})

add_library(http STATIC ${SOURCES})
include_directories(~/src/)

add_executable(http_server test/main.cpp)
target_link_libraries(  http_server http
                        pthread)

add_executable(test_thread test/thread_test.cpp)
target_link_libraries(test_thread ${Boost_LIBRARIES} -lboost_thread)


