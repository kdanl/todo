#include <gtest/gtest.h>

#include "../src/core/SimpleTask.hpp"
#include "../src/core/DeadlineTask.hpp"
#include "../src/core/RepeatingTask.hpp"
#include "../src/core/TaskStorage.hpp"



/* =========================
   SimpleTask
   ========================= */

TEST(SimpleTaskTest, Creation) {

    SimpleTask task(1,"Test task",Priority::Low);

    EXPECT_EQ(task.getId(),1);
    EXPECT_EQ(task.getTitle(),"Test task");
    EXPECT_FALSE(task.isComplete());
}

TEST(SimpleTaskTest, MarkDone) {

    SimpleTask task(1,"Task",Priority::Low);

    task.markDone();

    EXPECT_TRUE(task.isComplete());
}

TEST(SimpleTaskTest, ToStringContainsTitle) {

    SimpleTask task(1,"Buy milk",Priority::Low);

    std::string text = task.toString();

    EXPECT_NE(text.find("Buy milk"),std::string::npos);
}



/* =========================
   DeadlineTask
   ========================= */

TEST(DeadlineTaskTest, Creation) {

    DeadlineTask task(1,"Homework","2025-06-01",Priority::High);

    EXPECT_EQ(task.getDeadline(),"2025-06-01");
}

TEST(DeadlineTaskTest, TypeIsDeadline) {

    DeadlineTask task(1,"Homework","2025-06-01",Priority::High);

    EXPECT_EQ(task.getType(),"Deadline");
}

TEST(DeadlineTaskTest, ToStringContainsDeadline) {

    DeadlineTask task(1,"Homework","2025-06-01",Priority::High);

    std::string text = task.toString();

    EXPECT_NE(text.find("2025-06-01"),std::string::npos);
}



/* =========================
   RepeatingTask
   ========================= */

TEST(RepeatingTaskTest, Creation) {

    RepeatingTask task(1,"Workout","daily","08:00",Priority::Medium);

    EXPECT_EQ(task.getFrequency(),"daily");
    EXPECT_EQ(task.getTimeOfDay(),"08:00");
}

TEST(RepeatingTaskTest, TypeIsRepeating) {

    RepeatingTask task(1,"Workout","daily","08:00",Priority::Medium);

    EXPECT_EQ(task.getType(),"Repeating");
}

TEST(RepeatingTaskTest, ToStringContainsRepeatInfo) {

    RepeatingTask task(1,"Workout","daily","08:00",Priority::Medium);

    std::string text = task.toString();

    EXPECT_NE(text.find("daily"),std::string::npos);
    EXPECT_NE(text.find("08:00"),std::string::npos);
}



/* =========================
   TaskStorage
   ========================= */

TEST(TaskStorageTest, AddTask) {

    TaskStorage storage;

    storage.addTask(std::make_unique<SimpleTask>(1,"Task",Priority::Low));

    EXPECT_EQ(storage.getTaskCount(),1);
}

TEST(TaskStorageTest, FindById) {

    TaskStorage storage;

    storage.addTask(std::make_unique<SimpleTask>(1,"Task",Priority::Low));

    Task* task = storage.findById(1);

    ASSERT_NE(task,nullptr);
    EXPECT_EQ(task->getTitle(),"Task");
}

TEST(TaskStorageTest, RemoveTask) {

    TaskStorage storage;

    storage.addTask(std::make_unique<SimpleTask>(1,"Task",Priority::Low));

    bool removed = storage.removeTask(1);

    EXPECT_TRUE(removed);
    EXPECT_EQ(storage.getTaskCount(),0);
}

TEST(TaskStorageTest, FindByTitle) {

    TaskStorage storage;

    storage.addTask(std::make_unique<SimpleTask>(1,"Buy milk",Priority::Low));
    storage.addTask(std::make_unique<SimpleTask>(2,"Homework",Priority::Low));

    auto result = storage.findByTitle("milk");

    EXPECT_EQ(result.size(),1);
}

TEST(TaskStorageTest, CompletedCount) {

    TaskStorage storage;

    auto task = std::make_unique<SimpleTask>(1,"Task",Priority::Low);
    task->markDone();

    storage.addTask(std::move(task));

    EXPECT_EQ(storage.getCompletedCount(),1);
}

TEST(TaskStorageTest, ProgressPercentage) {

    TaskStorage storage;

    auto t1 = std::make_unique<SimpleTask>(1,"Task1",Priority::Low);
    auto t2 = std::make_unique<SimpleTask>(2,"Task2",Priority::Low);

    t1->markDone();

    storage.addTask(std::move(t1));
    storage.addTask(std::move(t2));

    auto progress = storage.getProgressPercentage();

    ASSERT_TRUE(progress.has_value());
    EXPECT_EQ(progress.value(),50);
}

TEST(TaskStorageTest, SortByPriority) {

    TaskStorage storage;

    storage.addTask(std::make_unique<SimpleTask>(1,"Low",Priority::Low));
    storage.addTask(std::make_unique<SimpleTask>(2,"High",Priority::High));

    storage.sortByPriority();

    const auto& tasks = storage.getTasks();

    EXPECT_EQ(tasks[0]->getPriority(),Priority::High);
}

TEST(TaskStorageTest, UpdateRepeatingTasksDoesNotCrash) {

    TaskStorage storage;

    storage.addTask(
        std::make_unique<RepeatingTask>(
            1,
            "Workout",
            "daily",
            "00:00",
            Priority::Low
        )
    );

    EXPECT_NO_THROW(storage.updateRepeatingTasks());
}