cmake_minimum_required(VERSION 3.20)

project(todo_cli)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(todo
        src/main.cpp

        src/cli/ArgumentParser.cpp

        src/core/Task.cpp
        src/core/SimpleTask.cpp
        src/core/DeadlineTask.cpp
        src/core/RepeatingTask.cpp
        src/core/TaskStorage.cpp

        src/storage/JsonFileStorage.cpp

        src/utils/DateUtils.cpp
)

target_include_directories(todo PRIVATE src)