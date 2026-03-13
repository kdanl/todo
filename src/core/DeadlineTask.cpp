#include "DeadlineTask.hpp"

DeadlineTask::DeadlineTask(int id, const std::string& title, const std::string& deadline, Priority priority)
    : Task(id, title, priority), deadline_(deadline) {}

const std::string& DeadlineTask::getDeadline() const {
    return deadline_;
}
std::string DeadlineTask::getType() const {
    return "Deadline";
}
std::string DeadlineTask::toString() const {
    std::string state;

    if (complete_) {
        state = "[x]";
    } else {
        state = "[ ]";
    }

    return state + " " + title_
           + " (deadline: " + deadline_
           + ", priority: " + priorityToString(priority_) + ")";
}