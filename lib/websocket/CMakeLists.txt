# minimun requirements
# my cmake cmake version 3.14.5
cmake_minimum_required(VERSION 3.9.4)
#project name
project(websocket)
# mark the cpp files as sources.
file(GLOB SOURCES "src/*.cpp")


add_library(websocket STATIC ${SOURCES})

# include util director and boost include directory
include_directories(../util/src)
include_directories(src/)
include_directories(${Boost_INCLUDE_DIRS})

# serach for boost libs.
link_directories(${Boost_LIB_DIRS} utils)

# web socket server.
add_executable(web_socket test/main.cpp)
target_link_libraries(web_socket websocket utils)

add_executable(test_coro test/test_coro.cpp)
target_link_libraries(test_coro boost_thread)
