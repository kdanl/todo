#include "SimpleTask.hpp"
SimpleTask::SimpleTask(int id, const std::string& title, int priority)
    : Task(id, title, priority) {}
std::string SimpleTask::toString() const{
    std::string state;
    if (complete_) {
        state = "[✓]";
    } else {
        state = "[ ]";
    }
    return state + " " + title_ + " (priority: " + std::to_string(priority_) + ")";
}
std::string SimpleTask::getType() const{
    return "Simple";
}