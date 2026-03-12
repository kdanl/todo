#pragma once

#include "Storage.hpp"
#include "../utils/Exceptions.hpp"
#include "../utils/Constants.hpp"

#include <string>

class JsonFileStorage : public Storage {
public:
    explicit JsonFileStorage(std::string filePath = std::string(Constants::DefaultStorageFile));

    void save(const TaskList& tasks) override;
    TaskList load() override;

private:
    std::string filePath_;
};