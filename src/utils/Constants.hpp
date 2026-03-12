#pragma once

#include <string_view>

namespace Constants {
    inline constexpr std::string_view DefaultStorageFile = "tasks.json"; // Файл хранения задач по умолчанию

    inline constexpr std::string_view DateFormat = "DD-MM-YYYY"; // Формат даты для дедлайнов
}
