cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(c_snake)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})  

file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(c_snake ${SRC_FILES})
target_include_directories(c_snake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(c_snake ${CURSES_LIBRARIES})