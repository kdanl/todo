# Todo CLI Task Manager

A console-based task manager written in modern C++.

The project provides a convenient command-line application for managing everyday tasks. It allows users to create, organize, search, filter, complete, and store tasks directly from the terminal.

The application is built using a modular architecture and demonstrates object-oriented design, modern C++ features, persistent JSON storage, and automated testing with GoogleTest.



# Project Purpose

The goal of this project is to provide a simple and efficient way to manage personal tasks directly from the command line.

The system allows users to:

- create and organize tasks
- assign priorities
- add deadlines
- mark tasks as completed
- search tasks by keyword
- filter tasks
- view statistics and progress
- store tasks between program runs

The project also demonstrates software engineering practices such as:

- modular architecture
- separation of concerns
- smart pointer based memory management
- type-safe command parsing
- automated testing
- build automation with CMake


# Features

The application supports the following functionality:

- Add new tasks with descriptive titles
- Set task priority (`Low`, `Medium`, `High`)
- Add deadlines to tasks
- Mark tasks as completed
- Search tasks by keyword
- View task statistics and progress
- Filter tasks by completion status
- Filter tasks by priority
- Sort tasks by priority
- Colorized terminal output
- Persistent storage using JSON
- Multiple task types

Supported task types:

- SimpleTask
- DeadlineTask
- RepeatingTask


# Command Line Usage

The program is executed from the terminal:

```
./todo <command> [arguments] [flags]
```


# Available Commands

## Help

Displays a list of available commands.

```
./todo help
```

## Add Task

Add a simple task.

```
./todo add "Do math homework"
```


## Add Task With Priority

```
./todo add "Finish homework" --priority high
```

Supported priorities:

- low
- medium
- high

## Add Task With Deadline

```
./todo add "Submit project report" --deadline 2026-03-25
```

Deadline format:

```
YYYY-MM-DD
```


## Mark Task As Completed

```
./todo done 3
```

Marks task with ID **3** as completed.


## Search Tasks

```
./todo search milk
```

Finds tasks containing the word **milk**.


## Show Statistics

```
./todo stats
```

Displays:

- total tasks
- completed tasks
- progress percentage


## List Completed Tasks

```
./todo list --done
```


## List Incomplete Tasks

```
./todo list --undone
```


## Filter Tasks By Priority

```
./todo list --priority high
```


## Example Workflow

```
./todo add "Buy milk"
./todo add "Finish C++ report" --priority high
./todo add "Submit project" --deadline 2026-03-25
./todo list
./todo done 2
./todo stats
./todo search project
```


# Project Structure

```
.
├── CMakeLists.txt
├── src
│
│   ├── main.cpp
│
│   ├── cli
│   │   ├── ArgumentParser.hpp
│   │   └── ArgumentParser.cpp
│
│   ├── core
│   │   ├── Task.hpp
│   │   ├── Task.cpp
│   │   ├── SimpleTask.hpp
│   │   ├── SimpleTask.cpp
│   │   ├── DeadlineTask.hpp
│   │   ├── DeadlineTask.cpp
│   │   ├── RepeatingTask.hpp
│   │   ├── RepeatingTask.cpp
│   │   ├── TaskStorage.hpp
│   │   └── TaskStorage.cpp
│
│   ├── storage
│   │   ├── Storage.hpp
│   │   ├── JsonFileStorage.hpp
│   │   └── JsonFileStorage.cpp
│
│   ├── utils
│   │   ├── Terminal.hpp
│   │   ├── Constants.hpp
│   │   ├── Exceptions.hpp
│   │   ├── DateUtils.hpp
│   │   └── DateUtils.cpp
│
└── tests
    ├── CMakeLists.txt
    ├── CLITests.cpp
    └── CoreTests.cpp
```


# Architecture Overview

The project is divided into three main modules:

- CLI Module
- Core Module
- Storage Module

Architecture flow:

```
User
  ↓
CLI Module
  ↓
Core Module
  ↓
Storage Module
```

# CLI Module

The CLI module handles all interaction between the user and the application.

Responsibilities:

- parsing command line input
- validating arguments
- converting raw input into structured command objects
- invoking functionality in the core module
- displaying formatted output


# Command Parsing

The main CLI parsing component is:

```
ArgumentParser
```

Responsibilities:

- reading command line arguments
- identifying commands
- validating parameters
- converting input into command structures

Supported commands:

- help
- add
- done
- list
- search
- stats


# Command Structures

Each command has its own structure:

- AddArguments
- DoneArguments
- ListArguments
- SearchArguments
- StatsArguments
- HelpArguments

These structures contain only the parameters required for the specific command.


# Optional Parameters

Optional command parameters are implemented using:

```
std::optional
```

Examples:

- optional priority
- optional deadline

This allows the program to detect whether a parameter was provided by the user.


# Command Representation

Commands are combined into a single type using:

```
std::variant
```

Example:

```
using UnderstandCommand = std::variant<
    AddArguments,
    ListArguments,
    DoneArguments,
    SearchArguments,
    StatsArguments,
    HelpArguments
>;
```


# Command Execution

Commands are executed using:

```
std::visit
```

This allows the program to execute logic depending on the command type stored in the variant.


# Terminal Output

The project includes a utility class:

```
Terminal
```

This class provides:

- colored output
- help messages
- error messages

Colorized output improves readability of terminal interaction.


# Core Module

The Core module implements the main task management logic.

It is responsible for:

- task representation
- task operations
- statistics
- sorting and filtering
- in-memory storage


# Task Hierarchy

The system uses an object-oriented architecture.

Base class:

```
Task
```

Derived classes:

- SimpleTask
- DeadlineTask
- RepeatingTask


# Base Class: Task

The abstract class `Task` stores common task data:

- task id
- title
- completion status
- priority

Methods:

- getId()
- getTitle()
- isComplete()
- markDone()
- markUndone()
- getPriority()
- setPriority()

Virtual methods implemented in derived classes:

- getType()
- toString()


# Task Types

## SimpleTask

Represents a basic task with:

- title
- priority
- completion state


## DeadlineTask

Represents a task with a deadline date.


## RepeatingTask

Represents tasks that repeat with a specified frequency and time of day.


# TaskStorage

The `TaskStorage` class manages tasks in memory.

Tasks are stored using:

```
std::vector<std::unique_ptr<Task>>
```

This ensures safe ownership and automatic memory management.

Operations include:

- addTask()
- removeTask()
- findById()
- findByTitle()
- getTasks()
- getTaskCount()
- getCompletedCount()
- getProgressPercentage()
- sortByPriority()
- updateRepeatingTasks()

The method **sortByPriority()** sorts tasks according to their priority level (High → Medium → Low) using `std::sort`.

The method **updateRepeatingTasks()** updates repeating tasks based on their frequency and time conditions.

Both methods are declared in **TaskStorage.hpp** and implemented in **TaskStorage.cpp**.


# Statistics

The system calculates:

- total number of tasks
- number of completed tasks
- progress percentage

Displayed using the `stats` command.


# Storage Module

The Storage module handles persistent storage of tasks.


# JsonFileStorage

Main storage class:

```
JsonFileStorage
```

Responsibilities:

- loading tasks from JSON
- saving tasks to JSON
- reconstructing task objects
- serializing task data


# Loading Tasks

At startup:

```
JsonFileStorage fileStorage;
TaskStorage storage;

storage.setTasks(fileStorage.load());
```

Tasks are loaded from disk.

---

# Saving Tasks

Before exit:

```
fileStorage.save(storage.getTasks());
```

This ensures all updates are saved.


# Build System

The project uses **CMake**.

C++ standard:

```
C++23
```

Main executable:

```
add_executable(todo ...)
```

---

# Build Instructions

Clone repository:

```
git clone <repository-url>
cd todo
```

Build project:

```
mkdir build
cd build
cmake ..
make
```

Run program:

```
./todo help
```


# Testing

Tests are implemented using **GoogleTest**.

Configured through CMake:

```
FetchContent
enable_testing()
add_subdirectory(tests)
```

Test files:

- CLITests.cpp
- CoreTests.cpp


# Modern C++ Features Used

The project demonstrates modern C++ features:

- std::unique_ptr
- std::variant
- std::visit
- std::optional
- enum class
- polymorphism
- RAII
- exception handling


# Contributors

Martynova Elina  
Tovmasyan Anna  
Kahle Daniel


# Summary

This project demonstrates a modular console application built with modern C++.

It combines:

- command-line interaction
- object-oriented task modeling
- persistent storage
- automated testing
- safe memory management

The result is a functional and extensible CLI task manager suitable both as a practical tool and as an educational example of modern C++ architecture.