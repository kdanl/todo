#include "TaskStorage.hpp"
#include <algorithm>
void TaskStorage::addTask(std::unique_ptr<Task> task) {
    tasks_.push_back(std::move(task));
}
std::vector<Task*> TaskStorage::findByTitle(const std::string& keyword)const {
    std::vector<Task*> result;
    for (const auto& t : tasks_) {
        if (t->getTitle().find(keyword) != std::string::npos) {
            result.push_back(t.get());
        }
    }return result;
}
int TaskStorage::getTaskCount() const {
    return tasks_.size();
}
int TaskStorage::getCompletedCount() const {
    int kol = 0;
    for (const auto& task : tasks_) {
        if (task->isComplete()) {
            kol++;
        }
    }
    return kol;
}
Task* TaskStorage::findById(int id) const{
    for (const auto& t : tasks_) {
        if (t->getId() == id) {
            return t.get();
        }
    }return nullptr;
}

bool TaskStorage::removeTask(int id) {
    for (auto a = tasks_.begin(); a != tasks_.end(); ++a) {
        if ((*a)->getId() == id) {
            tasks_.erase(a);
            return true;
        }
    }return false;
}
const std::vector<std::unique_ptr<Task>>& TaskStorage::getTasks() const {
    return tasks_;
}
void TaskStorage::sortByPriority() {
    std::sort(tasks_.begin(), tasks_.end(),
        [](const std::unique_ptr<Task>& a1, const std::unique_ptr<Task>& a2) {
            return static_cast<int>(a1->getPriority()) >
                   static_cast<int>(a2->getPriority());
        });
}
std::optional<int> TaskStorage::getProgressPercentage() const {
    int tasks_count = getTaskCount();
    if (tasks_count == 0) {
        return std::nullopt;
    }
    int complete = getCompletedCount();
    return complete *100 /tasks_count;
}
