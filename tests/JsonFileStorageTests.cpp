#include <gtest/gtest.h>

#include "storage/JsonFileStorage.hpp"
#include "core/SimpleTask.hpp"
#include "core/DeadlineTask.hpp"
#include "core/RepeatingTask.hpp"

#include <filesystem>
#include <fstream>

static const std::string TEST_FILE = "test_tasks.json";

class JsonFileStorageTest : public ::testing::Test {
protected:

    void TearDown() override {
        std::filesystem::remove(TEST_FILE);
    }
};

TEST_F(JsonFileStorageTest, SaveAndLoadSingleTask) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    tasks.push_back(
        std::make_unique<SimpleTask>(1, "Test task", Priority::Low)
    );

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded[0]->getTitle(), "Test task");
}

TEST_F(JsonFileStorageTest, SaveMultipleTasks) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    tasks.push_back(std::make_unique<SimpleTask>(1, "Task1", Priority::Low));
    tasks.push_back(std::make_unique<SimpleTask>(2, "Task2", Priority::High));

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 2);

    EXPECT_EQ(loaded[0]->getTitle(), "Task1");
    EXPECT_EQ(loaded[1]->getTitle(), "Task2");
}

TEST_F(JsonFileStorageTest, SaveDeadlineTask) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    tasks.push_back(
        std::make_unique<DeadlineTask>(
            1,
            "Submit report",
            "2025-06-01",
            Priority::High
        )
    );

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded[0]->getType(), "Deadline");
}

TEST_F(JsonFileStorageTest, SaveRepeatingTask) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    tasks.push_back(
        std::make_unique<RepeatingTask>(
            1,
            "Workout",
            "daily",
            "08:00",
            Priority::Medium
        )
    );

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded[0]->getType(), "Repeating");
}

TEST_F(JsonFileStorageTest, SaveCompletedTask) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    auto task = std::make_unique<SimpleTask>(1, "Done task", Priority::Low);

    task->markDone();

    tasks.push_back(std::move(task));

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_TRUE(loaded[0]->isComplete());
}

TEST_F(JsonFileStorageTest, PriorityIsPreserved) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    tasks.push_back(
        std::make_unique<SimpleTask>(1, "Important", Priority::High)
    );

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded[0]->getPriority(), Priority::High);
}

TEST_F(JsonFileStorageTest, LoadEmptyFileReturnsEmptyList) {

    JsonFileStorage storage(TEST_FILE);

    auto tasks = storage.load();

    EXPECT_TRUE(tasks.empty());
}

TEST_F(JsonFileStorageTest, OverwriteFile) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks1;

    tasks1.push_back(
        std::make_unique<SimpleTask>(1, "Old", Priority::Low)
    );

    storage.save(tasks1);

    TaskList tasks2;

    tasks2.push_back(
        std::make_unique<SimpleTask>(2, "New", Priority::High)
    );

    storage.save(tasks2);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded[0]->getTitle(), "New");
}

TEST_F(JsonFileStorageTest, StringEscapingWorks) {

    JsonFileStorage storage(TEST_FILE);

    TaskList tasks;

    tasks.push_back(
        std::make_unique<SimpleTask>(
            1,
            "Quote \" test",
            Priority::Low
        )
    );

    storage.save(tasks);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded[0]->getTitle(), "Quote \" test");
}

TEST_F(JsonFileStorageTest, MissingFileDoesNotThrow) {

    JsonFileStorage storage(TEST_FILE);

    EXPECT_NO_THROW(storage.load());
}