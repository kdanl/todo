#ifndef TASKSTORAGE_HPP
#define TASKSTORAGE_HPP
#include <memory>
#include <vector>
#include <optional>
#include "Task.hpp"
class TaskStorage{
private:
    std::vector<std::unique_ptr<Task>> tasks_;
public:
    void addTask(std::unique_ptr<Task> task);
    Task* findById(int id) const;
    bool removeTask(int id);
    const std::vector<std::unique_ptr<Task>>& getTasks() const;
    std::vector<Task*> findByTitle(const std::string& keyword) const;
    int getTaskCount() const;
    int getCompletedCount() const;
    std::optional<int> getProgressPercentage()const;
    void sortByPriority();
};
#endif