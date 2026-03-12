#include "Task.hpp"

Task::Task(int id, const std::string& title, int priority) : id_(id),title_(title), complete_(false),priority_(priority){}

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
int Task::getPriority() const {
    return priority_;
}

void Task::SetPriority(int newPriority) {
    priority_ = newPriority;
}