
cmake_minimum_required(VERSION 3.24)

project(FileAES)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(encrypt encrypt.cpp)
add_executable(decrypt decrypt.cpp)
