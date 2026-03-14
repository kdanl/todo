#pragma once
#include "Task.hpp"
class SimpleTask : public Task {
public:
    SimpleTask(int id, const std::string& title, Priority priority);
    std::string getType() const override;
    std::string toString() const override;
};
