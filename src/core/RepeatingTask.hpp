#pragma once
#include "Task.hpp"
#include <string>
class RepeatingTask : public Task {
public:
    RepeatingTask(int id,
                  const std::string& title,
                  const std::string& frequency,
                  const std::string& timeOfDay,
                  Priority priority);
    std::string getType() const override;
    std::string toString() const override;
    const std::string& getFrequency() const;
    const std::string& getTimeOfDay() const;
    void updateByTime();

private:
    std::string frequency_;
    std::string timeOfDay_;
};