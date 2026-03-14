#pragma once

#include "Task.hpp"
#include <string>

class DeadlineTask : public Task {
private:
    std::string deadline_;

public:
    DeadlineTask(int id, const std::string& title, const std::string& deadline, Priority priority);

    const std::string& getDeadline() const;
    std::string getType() const override;
    std::string toString() const override;
};
