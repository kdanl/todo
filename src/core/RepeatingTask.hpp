#ifndef REPEATINGTASK_HPP
#define REPEATINGTASK_HPP
#include "Task.hpp"
#include <string>
class RepeatingTask : public Task {
private:
    std::string frequency_;
    std::string timeOfDay_;
public:
    RepeatingTask(int id, const std::string& title, const std::string& frequency, const std::string& timeOfDay, int priority);
    std::string getType() const override;
    std::string toString() const override;
    const std::string& getFrequency() const;
    const std::string& getTimeOfDay()const;
};
#endif