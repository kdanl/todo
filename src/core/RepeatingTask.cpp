#include "RepeatingTask.hpp"
RepeatingTask::RepeatingTask(int id,
                             const std::string& title,
                             const std::string& frequency,
                             const std::string& timeOfDay,
                             Priority priority)
    : Task(id, title, priority), frequency_(frequency), timeOfDay_(timeOfDay) {}
std::string RepeatingTask::getType() const {
    return "Repeating";
}
std::string RepeatingTask::toString() const {
    std::string state;
    if (complete_) {
        state = "[x]";
    } else {
        state = "[ ]";
    }
    return state + " " + title_
           + " (" + frequency_ + " at " + timeOfDay_
           + ", priority: " + priorityToString(priority_) + ")";
}
const std::string &RepeatingTask::getFrequency() const {
    return frequency_;
}
const std::string &RepeatingTask::getTimeOfDay() const {
    return timeOfDay_;
}