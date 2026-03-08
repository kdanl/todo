#pragma once

#include <vector>
#include <memory>

class Task;

class Storage {
public:
    virtual ~Storage() = default;

    virtual void save(const std::vector<std::unique_ptr<Task>>& tasks) = 0;

    virtual std::vector<std::unique_ptr<Task>> load() = 0;
};
