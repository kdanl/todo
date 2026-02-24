cmake_minimum_required(VERSION 4.1)
project(todo)

set(CMAKE_CXX_STANDARD 23)

add_executable(todo scr/main.cpp
        scr/cli/ArgumentParser.cpp
        scr/cli/ArgumentParser.hpp
        scr/cli/Command.hpp
        scr/cli/CommandFactory.hpp
        scr/cli/AddCommand.hpp
        scr/cli/ListCommand.hpp
        scr/cli/DoneCommand.hpp
        scr/core/Task.hpp
        scr/core/SimpleTask.hpp
        scr/core/DeadlineTask.hpp
        scr/core/RecurringTask.hpp
        scr/core/TaskRepository.hpp
        scr/storage/Storage.hpp
        scr/storage/JsonFileStorage.hpp
        scr/storage/JsonFileStorage.cpp
        scr/utils/Exceptions.hpp
        scr/utils/Constants.hpp
        tests/TaskTests.cpp
        tests/RepositoryTests.cpp
        tests/ParserTests.cpp
)
