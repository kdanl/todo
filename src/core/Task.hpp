#pragma once
#include <string>
enum class Priority {
    Low,
    Medium,
    High
};
std::string priorityToString(Priority p);
Priority priorityFromString(const std::string& str);
class Task {
protected:
    int id_;
    std::string title_;
    bool complete_;
    Priority priority_;

public:
    Task(int id, const std::string& title, Priority priority);
    virtual ~Task() = default;

    int getId() const;
    const std::string& getTitle() const;
    bool isComplete() const;
    Priority getPriority() const;

    void markDone();
    void markUndone();
    void setTitle(const std::string& title);
    void setPriority(Priority newPriority);
    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
};
