#include "DateUtils.hpp"

#include <cctype>
#include <optional>
#include <string_view>

std::optional<Date> parseDate(std::string_view text) {
    // Ожидаем формат DD-MM-YYYY (10 символов)
    if (text.size() != 10) {
        return std::nullopt;
    }

    if (text[2] != '-' || text[5] != '-') {
        return std::nullopt;
    }

    auto is_digits = [](std::string_view s) {
        for (char ch : s) {
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                return false;
            }
        }
        return true;
    };

    std::string_view day_sv   = text.substr(0, 2);
    std::string_view month_sv = text.substr(3, 2);
    std::string_view year_sv  = text.substr(6, 4);

    if (!is_digits(year_sv) || !is_digits(month_sv) || !is_digits(day_sv)) {
        return std::nullopt;
    }

    auto to_int = [](std::string_view sv) {
        int value = 0;
        for (char ch : sv) {
            value = value * 10 + (ch - '0');
        }
        return value;
    };

    int year  = to_int(year_sv);
    int month = to_int(month_sv);
    int day   = to_int(day_sv);

    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) { // Валидация диапазонов
        return std::nullopt;
    }

    return Date{day, month, year};
}

int compare(const Date& lhs, const Date& rhs) {
    if (lhs.year != rhs.year) {
        return (lhs.year < rhs.year) ? -1 : 1;
    }
    if (lhs.month != rhs.month) {
        return (lhs.month < rhs.month) ? -1 : 1;
    }
    if (lhs.day != rhs.day) {
        return (lhs.day < rhs.day) ? -1 : 1;
    }
    return 0;
}
