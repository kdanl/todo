#include "SimpleTask.hpp"

SimpleTask::SimpleTask(int id, const std::string& title, Priority priority)
    : Task(id, title, priority) {}

std::string SimpleTask::getType() const {
    return "Simple";
}

std::string SimpleTask::toString() const {
    std::string state;

    if (complete_) {
        state = "[x]";
    } else {
        state = "[ ]";
    }

    return state + " " + title_ + " (priority: " + priorityToString(priority_) + ")";
}