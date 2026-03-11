#pragma once

#include <optional>
#include <string_view>

struct Date {
    int day{};
    int month{};
    int year{};
};

// Пытается спарсить строку формата "DD-MM-YYYY".
// Возвращает std::nullopt, если формат некорректен.
std::optional<Date> parseDate(std::string_view text);

// Сравнение дат для сортировки
int compare(const Date& lhs, const Date& rhs);

// Сортировка по дедлайну
inline bool operator<(const Date& lhs, const Date& rhs) {
    return compare(lhs, rhs) < 0;
}
