#include "Task.hpp"

Task::Task(int id, const std::string& title) : id_(id),title_(title), complete_(false){}

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