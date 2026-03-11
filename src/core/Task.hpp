#ifndef TASK_HPP
#define TASK_HPP
#include <string>
class Task {
protected:
    int id_;
    std::string title_;
    bool complete_;

public:
    Task(int id, const std::string& title);
    virtual ~Task() = default;

    int getId() const;
    const std::string& getTitle() const;
    bool isComplete() const;

    void markDone();
    void markUndone();

    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
    void setTitle(const std::string& title);
};
#endif