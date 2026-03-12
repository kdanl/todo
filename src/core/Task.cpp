#include "Task.hpp"
#include <stdexcept>
std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::Low: return "Low";
        case Priority::Medium: return "Medium";
        case Priority::High: return "High";
    }
    return "Unknown";
}
Priority priorityFromString(const std::string& str) {
    if (str == "low" || str == "Low") {
        return Priority::Low;
    }
    if (str == "medium" || str == "Medium") {
        return Priority::Medium;
    }
    if (str == "high" || str == "High") {
        return Priority::High;
    }
    throw std::invalid_argument("Invalid priority value");
}
Task::Task(int id, const std::string& title, Priority priority)
    : id_(id), title_(title), complete_(false), priority_(priority) {}
int Task::getId() const {
    return id_;
}
const std::string& Task::getTitle() const {
    return title_;
}
bool Task::isComplete() const {
    return complete_;
}
void Task::markDone() {
    complete_ = true;
}

void Task::markUndone() {
    complete_ = false;
}
void Task::setTitle(const std::string &title) {
    title_ = title;
}
Priority Task::getPriority() const {
    return priority_;
}

void Task::setPriority(Priority newPriority) {
    priority_ = newPriority;
}