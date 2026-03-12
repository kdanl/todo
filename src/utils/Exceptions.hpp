#pragma once

#include <stdexcept>
#include <string>

class TodoError : public std::runtime_error { // Базовое исключение
public:
    explicit TodoError(const std::string& message) : std::runtime_error(message) {}

    explicit TodoError(const char* message) : std::runtime_error(message) {}
};


class ParseError : public TodoError { // Ошибки аргументов
public:
    using TodoError::TodoError;
};


class StorageError : public TodoError { // Ошибки хранения
public:
    using TodoError::TodoError;
};


class LogicError : public TodoError {  // Ошибки логики
public:
    using TodoError::TodoError;
};
