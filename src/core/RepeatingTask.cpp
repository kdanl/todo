#include "RepeatingTask.hpp"
RepeatingTask::RepeatingTask(int id,const std::string& title,const std::string& frequency,const std::string& timeOfDay)
    : Task(id, title), frequency_(frequency), timeOfDay_(timeOfDay) {}
std::string RepeatingTask::getType() const {
    return "Repeating";
}
std::string RepeatingTask::toString() const {
    std::string state;
    if (complete_) {
        state = "[✓]";
    } else {
        state = "[x]";
    }
    return state + " " + title_+ " (" + frequency_ + " at " + timeOfDay_ + ")";
}
const std::string &RepeatingTask::getFrequency() const {
    return frequency_;
}
const std::string &RepeatingTask::getTimeOfDay() const {
    return timeOfDay_;
}