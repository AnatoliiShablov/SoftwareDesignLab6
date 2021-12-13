cmake_minimum_required(VERSION 3.21)

project(SD6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Tokenizer)
add_subdirectory(Visitor)

add_executable(SD6 main.cpp)
