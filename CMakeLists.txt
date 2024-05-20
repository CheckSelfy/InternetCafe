cmake_minimum_required(VERSION 3.22)
project(InternetCafe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE source RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(internet_cafe ${source})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY test.py DESTINATION ${CMAKE_BINARY_DIR})
