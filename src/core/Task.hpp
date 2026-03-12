#ifndef TASK_HPP
#define TASK_HPP
#include <string>
class Task {
protected:
    int id_;
    std::string title_;
    bool complete_;
    int priority_;

public:
    Task(int id, const std::string& title,int priority);
    virtual ~Task() = default;

    int getId() const;
    const std::string& getTitle() const;
    bool isComplete() const;
    int getPriority() const;

    void markDone();
    void markUndone();
    void setTitle(const std::string& title);
    void SetPriority(int newPriority);
    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
};

#endif