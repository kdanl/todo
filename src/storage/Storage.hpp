#pragma once

#include <vector>
#include <memory>

class Task;

using TaskPtr  = std::unique_ptr<Task>;
using TaskList = std::vector<TaskPtr>;


class Storage {
public:
    virtual ~Storage() = default;

    virtual void save(const TaskList& tasks) = 0;

    virtual TaskList load() = 0;
};