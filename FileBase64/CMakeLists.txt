
cmake_minimum_required(VERSION 3.24)

project(FileBase64)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(encode encode.cpp)
add_executable(decode decode.cpp)
