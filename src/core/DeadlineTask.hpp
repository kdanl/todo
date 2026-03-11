#ifndef DEADLINE_TASK_HPP
#include "Task.hpp"
#include <string>
class DeadlineTask : public Task {
private:
    std::string deadline_;
public:
    DeadlineTask(int id, const std::string& title, const std::string& deadline);//Чтобы не копировать строку.Это быстрее.
    const std::string& getDeadline() const {
    }
    void setDeadline(const std::string& deadline) {
    }
    std::string getType() const override;
    std::string toString() const override;//override - Я переопределяю виртуальную функцию из базового класса
};
#endif