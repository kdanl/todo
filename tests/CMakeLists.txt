add_executable(todo_tests
        JsonFileStorageTests.cpp
        CoreTests.cpp
        CLITests.cpp

        ../src/core/Task.cpp
        ../src/core/SimpleTask.cpp
        ../src/core/DeadlineTask.cpp
        ../src/core/RepeatingTask.cpp
        ../src/core/TaskStorage.cpp

        ../src/storage/JsonFileStorage.cpp

        ../src/utils/DateUtils.cpp

        ../src/cli/ArgumentParser.cpp
)

target_include_directories(todo_tests
        PRIVATE ../src
)

target_link_libraries(todo_tests
        gtest
        gtest_main
)

add_test(NAME todo_tests COMMAND todo_tests)