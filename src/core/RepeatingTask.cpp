#include "RepeatingTask.hpp"
#include <chrono>
#include <ctime>

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

void RepeatingTask::updateByTime() {

    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);

    std::tm* local = std::localtime(&t);

    if (!local) return; // Защита если localtime не смог получить время

    int currentHour = local->tm_hour;
    int currentMinute = local->tm_min;

    if (timeOfDay_.size() < 5) return; // защита формата HH:MM

    int taskHour = std::stoi(timeOfDay_.substr(0,2));
    int taskMinute = std::stoi(timeOfDay_.substr(3,2));

    if (currentHour > taskHour ||
        (currentHour == taskHour && currentMinute >= taskMinute)) {

        complete_ = false;
        }
}