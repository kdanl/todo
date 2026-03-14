
#pragma once
#include <optional>
#include <string>
#include <variant>


struct AddArguments {
    std::string title;
    std::optional<std::string> priority;
    std::optional<std::string> deadline;
    std::optional<std::string> repeat;
    std::optional<std::string> timeOfDay;
};
struct ListArguments {
    bool ifDone=false;
    bool ifUndone=false;
    std::optional<std::string> priorityFilter;
    std::optional<std::string> sortFilter;
};
struct DoneArguments {
    int id;
};
struct SearchArguments {
    std::string word;
};
struct StatsArguments {
};
struct HelpArguments {
};
using UnderstandCommand = std::variant<
    AddArguments,
    ListArguments,
    DoneArguments,
    SearchArguments,
    StatsArguments,
    HelpArguments
>;
class ArgumentParser {
public:
    UnderstandCommand parse(int arg_quant,char* arg_vec[]) const;
};
