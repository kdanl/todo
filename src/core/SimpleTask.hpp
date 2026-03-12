#ifndef SIMPLETASK_HPP
#define SIMPLETASK_HPP
#include "Task.hpp"
class SimpleTask : public Task {
public:
    SimpleTask(int id, const std::string& title, int priority);
    std::string getType() const override;
    std::string toString() const override;
};

#endif