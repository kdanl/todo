#include "JsonFileStorage.hpp"

#include "../core/DeadlineTask.hpp"
#include "../core/RepeatingTask.hpp"
#include "../core/SimpleTask.hpp"
#include "../core/Task.hpp"
#include "../utils/Exceptions.hpp"

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace {

std::string escape_json(std::string_view s) {

    std::string out;
    out.reserve(s.size() + 8);

    for (char ch : s) {

        switch (ch) {
        case '\\': out += "\\\\"; break;
        case '"':  out += "\\\""; break;
        case '\n': out += "\\n"; break;
        case '\r': out += "\\r"; break;
        case '\t': out += "\\t"; break;
        default:   out += ch; break;
        }
    }

    return out;
}

std::optional<std::string> parse_string_field(std::string_view obj, std::string_view key) {

    const std::string pattern = "\"" + std::string(key) + "\"";

    std::size_t pos = obj.find(pattern);
    if (pos == std::string_view::npos) return std::nullopt;

    pos = obj.find(':', pos);
    if (pos == std::string_view::npos) return std::nullopt;

    pos = obj.find('"', pos);
    if (pos == std::string_view::npos) return std::nullopt;

    ++pos;

    bool escape = false;
    std::string value;

    for (std::size_t i = pos; i < obj.size(); ++i) {

        char ch = obj[i];

        if (escape) {

            switch (ch) {
            case 'n': value.push_back('\n'); break;
            case 'r': value.push_back('\r'); break;
            case 't': value.push_back('\t'); break;
            case '\\': value.push_back('\\'); break;
            case '"': value.push_back('"'); break;
            default: value.push_back(ch); break;
            }

            escape = false;
            continue;
        }

        if (ch == '\\') {
            escape = true;
            continue;
        }

        if (ch == '"') {
            return value;
        }

        value.push_back(ch);
    }

    return std::nullopt;
}

std::optional<int> parse_int_field(std::string_view obj, std::string_view key) {

    const std::string pattern = "\"" + std::string(key) + "\"";

    std::size_t pos = obj.find(pattern);
    if (pos == std::string_view::npos) return std::nullopt;

    pos = obj.find(':', pos);
    if (pos == std::string_view::npos) return std::nullopt;

    ++pos;

    while (pos < obj.size() && obj[pos] == ' ') ++pos;

    bool neg = false;

    if (pos < obj.size() && obj[pos] == '-') {
        neg = true;
        ++pos;
    }

    if (pos >= obj.size() || obj[pos] < '0' || obj[pos] > '9') {
        return std::nullopt;
    }

    int value = 0;

    while (pos < obj.size() && obj[pos] >= '0' && obj[pos] <= '9') {
        value = value * 10 + (obj[pos] - '0');
        ++pos;
    }

    return neg ? -value : value;
}

std::optional<bool> parse_bool_field(std::string_view obj, std::string_view key) {

    const std::string pattern = "\"" + std::string(key) + "\"";

    std::size_t pos = obj.find(pattern);
    if (pos == std::string_view::npos) return std::nullopt;

    pos = obj.find(':', pos);
    if (pos == std::string_view::npos) return std::nullopt;

    ++pos;

    while (pos < obj.size() && obj[pos] == ' ') ++pos;

    if (obj.substr(pos, 4) == "true")  return true;
    if (obj.substr(pos, 5) == "false") return false;

    return std::nullopt;
}

std::vector<std::string_view> split_task_objects(const std::string& json_str) {

    std::string_view json(json_str);
    std::vector<std::string_view> objects;

    std::size_t tasks_pos = json.find("\"tasks\"");
    if (tasks_pos == std::string_view::npos) return objects;

    std::size_t arr_start = json.find('[', tasks_pos);
    if (arr_start == std::string_view::npos) return objects;

    std::size_t arr_end = json.find(']', arr_start);
    if (arr_end == std::string_view::npos) return objects;

    std::string_view arr = json.substr(arr_start + 1, arr_end - arr_start - 1);

    std::size_t i = 0;

    while (i < arr.size()) {

        while (i < arr.size() &&
               (arr[i] == ' ' || arr[i] == '\n' || arr[i] == '\r' || arr[i] == '\t' || arr[i] == ',')) {
            ++i;
        }

        if (i >= arr.size()) break;

        if (arr[i] != '{') {
            ++i;
            continue;
        }

        std::size_t start = i;
        int depth = 0;

        for (; i < arr.size(); ++i) {

            if (arr[i] == '{') ++depth;

            else if (arr[i] == '}') {

                --depth;

                if (depth == 0) {
                    objects.push_back(arr.substr(start, i - start + 1));
                    ++i;
                    break;
                }
            }
        }
    }

    return objects;
}

}

JsonFileStorage::JsonFileStorage(std::string filePath)
    : filePath_(std::move(filePath)) {}

void JsonFileStorage::save(const TaskList& tasks) {

    std::ofstream out(filePath_, std::ios::binary | std::ios::trunc);

    if (!out.is_open()) {
        throw StorageError("Cannot open storage file for writing: " + filePath_);
    }

    out << "{\n  \"tasks\": [\n";

    for (std::size_t i = 0; i < tasks.size(); ++i) {

        const Task& t = *tasks[i];

        out << "    {"
            << "\"id\": " << t.getId() << ", "
            << "\"title\": \"" << escape_json(t.getTitle()) << "\", "
            << "\"done\": " << (t.isComplete() ? "true" : "false") << ", "
            << "\"type\": \"" << escape_json(t.getType()) << "\", "
            << "\"priority\": \"" << escape_json(priorityToString(t.getPriority())) << "\"";

        if (t.getType() == "Repeating") {

            const auto& rt = static_cast<const RepeatingTask&>(t);

            out << ", "
                << "\"frequency\": \"" << escape_json(rt.getFrequency()) << "\", "
                << "\"timeOfDay\": \"" << escape_json(rt.getTimeOfDay()) << "\"";
        }

        if (t.getType() == "Deadline") {

            const auto& rt = static_cast<const DeadlineTask&>(t);

            out << ", "
                << "\"deadline\": \"" << escape_json(rt.getDeadline()) << "\"";
        }

        out << "}";

        if (i + 1 < tasks.size()) {
            out << ",";
        }

        out << "\n";
    }

    out << "  ]\n}\n";

    if (!out.good()) {
        throw StorageError("Failed while writing storage file: " + filePath_);
    }
}

TaskList JsonFileStorage::load() {

    std::ifstream in(filePath_, std::ios::binary);

    if (!in.is_open()) {
        return {};
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();

    const std::string content = buffer.str();

    TaskList tasks;

    for (std::string_view obj : split_task_objects(content)) {

        auto id = parse_int_field(obj, "id");
        auto title = parse_string_field(obj, "title");
        auto done = parse_bool_field(obj, "done");
        auto type = parse_string_field(obj, "type");
        auto priority = parse_string_field(obj, "priority");

        if (!id || !title || !done || !type) {
            throw StorageError("Invalid task object in storage file: " + filePath_);
        }

        Priority p = Priority::Low;

        if (priority) {
            p = priorityFromString(*priority);
        }

        std::unique_ptr<Task> task;

        if (*type == "Simple") {
            task = std::make_unique<SimpleTask>(*id, *title, p);
        }

        else if (*type == "Repeating") {

            auto frequency = parse_string_field(obj, "frequency");
            auto timeOfDay = parse_string_field(obj, "timeOfDay");

            if (!frequency || !timeOfDay) {
                throw StorageError("Invalid repeating task in storage file: " + filePath_);
            }

            task = std::make_unique<RepeatingTask>(*id, *title, *frequency, *timeOfDay, p);
        }

        else if (*type == "Deadline") {

            auto deadline = parse_string_field(obj, "deadline");

            if (!deadline) {
                throw StorageError("Invalid deadline task in storage file: " + filePath_);
            }

            task = std::make_unique<DeadlineTask>(*id, *title, *deadline, p);
        }

        else {
            throw StorageError("Unknown task type: " + *type);
        }

        if (*done) {
            task->markDone();
        }

        tasks.push_back(std::move(task));
    }

    return tasks;
}