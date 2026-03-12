#include "DeadlineTask.hpp"

DeadlineTask::DeadlineTask(int id, const std::string &title, const std::string &deadline):Task(id,title),deadline_(deadline) {
}
const std::string& DeadlineTask::getDeadline() const {
    return deadline_;
}
void DeadlineTask::setDeadline(const std::string& deadline) {
    deadline_ = deadline;
}
std::string DeadlineTask::getType() const {
    return "Deadline";
}
std::string DeadlineTask::toString() const {
    std::string status = complete_ ? "[✓] " : "[ ] ";
    return status + getTitle() + " (eadline: " + deadline_ + ")";
}
