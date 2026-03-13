//ArgumentParser переводит массив строк в структуру данных.
#pragma once
#include <optional>
#include <string>
#include <variant>


struct AddArguments { //хранит данные для команды добавления задачи
    std::string title;
    std::optional<std::string> priority;
    std::optional<std::string> deadline;
    std::optional<std::string> repeat;
    std::optional<std::string> timeOfDay;
};
struct ListArguments { //хранит настройки отображения списка задач
    bool ifDone=false;
    bool ifUndone=false; //присваиваю фолс тк это начальное значение иначе будет мусор
    std::optional<std::string> priorityFilter; //eсли написал --priority high будет "high".
    std::optional<std::string> sortFilter;
};
struct DoneArguments { //хранит номер задачи
    int id;
};
struct SearchArguments { //хранит слово для поиска задач
    std::string word;
};
struct StatsArguments { //пользователь хочет посмотреть статистику задач
};
struct HelpArguments { //пользователь хочет увидеть справку программы
};
using UnderstandCommand = std::variant< //одна функция parse() всегда возвращает один тип UnderstandCommand а внутри уже может скрываться любая из команд.
    AddArguments,
    ListArguments,
    DoneArguments,
    SearchArguments,
    StatsArguments,
    HelpArguments
>;
class ArgumentParser {
public:
    UnderstandCommand parse(int arg_quant,char* arg_vec[]) const; //char* - указатель на строку, char* [] - указатель на массив
};
//Поэтому роль ArgumentParser:разобрать ввод пользователя и превратить его в понятную структуру.
