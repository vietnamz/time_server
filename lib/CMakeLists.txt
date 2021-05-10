# minimun requirements
# my cmake cmake version 3.14.5
cmake_minimum_required(VERSION 3.9.4)
#project name
project(ott)

include_directories("./")

add_subdirectory(util)
#add_subdirectory(datasource)
add_subdirectory(http)
add_subdirectory(websocket)
