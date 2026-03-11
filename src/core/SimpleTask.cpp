#include "SimpleTask.hpp"
SimpleTask::SimpleTask(int id,const std::string& title):Task(id, title) {}
std::string SimpleTask::toString() const{
    std::string state;
    if (complete_) {
        state = "[✓]";
    } else {
        state = "[х]";
    }
    return status + " ID: "+std::to_string(id_)+" | "+ title_ +" | type: Simple";
}
std::string SimpleTask::getType() const{
    return "Simple";
}