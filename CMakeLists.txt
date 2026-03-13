cmake_minimum_required(VERSION 3.20)

project(todo_cli)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(todo
        src/main.cpp

        src/cli/ArgumentParser.cpp

        src/core/Task.cpp
        src/core/SimpleTask.cpp

        src/core/DeadlineTask.hpp
        src/core/DeadlineTask.cpp
        src/core/RecurringTask.hpp
        src/core/TaskRepository.hpp
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
        src/core/RepeatingTask.cpp
        src/core/TaskStorage.cpp

        src/storage/JsonFileStorage.cpp

        src/utils/DateUtils.cpp

)
target_include_directories(todo PRIVATE src)