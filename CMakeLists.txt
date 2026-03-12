cmake_minimum_required(VERSION 3.20)

project(todo_cli)

set(CMAKE_CXX_STANDARD 23)

add_executable(todo
        src/main.cpp
        src/cli/ArgumentParser.cpp
        src/cli/ArgumentParser.hpp
        src/cli/Command.hpp
        src/cli/CommandFactory.hpp
        src/cli/AddCommand.hpp
        src/cli/ListCommand.hpp
        src/cli/DoneCommand.hpp
        src/core/Task.hpp
        src/core/SimpleTask.hpp
        src/core/DeadlineTask.hpp
        src/core/RepeatingTask.hpp
        src/core/RepeatingTask.hpp
        src/storage/Storage.hpp
        src/storage/JsonFileStorage.hpp
        src/storage/JsonFileStorage.cpp
        src/utils/Exceptions.hpp
        src/utils/Constants.hpp
        tests/TaskTests.cpp
        tests/RepositoryTests.cpp
        tests/ParserTests.cpp
        src/cli/terminal.hpp
        src/core/DeadlineTask.cpp
        src/core/Task.cpp
)

target_include_directories(todo PRIVATE src)