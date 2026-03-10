cmake_minimum_required(VERSION 3.20)

project(todo_cli)

set(CMAKE_CXX_STANDARD 23)

add_executable(todo
        src/main.cpp
        src/cli/ArgumentParser.cpp
)

target_include_directories(todo PRIVATE src)