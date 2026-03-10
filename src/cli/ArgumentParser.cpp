#include "ArgumentParser.hpp"
#include <stdexcept>
#include <string>

UnderstandCommand ArgumentParser::parse(int arg_quant, char *arg_vec[]) const {
    if (arg_quant<2) {
        return HelpArguments{}; //если аргументов меньше чем два то мы открываем пользователю справку тк не ввел ничего кроме имени программы
    }
    std::string command = arg_vec[1]; //берем второй аргумент после command
    if (command=="help") { //если пользователь ввел хелп
        return HelpArguments{};
    }
    if (command=="stats") {
        return StatsArguments{};
    }
    if (command=="list") {
        return ListArguments{};
    }
    if (command=="done") {
        if (arg_quant<3) { //todо done 3 arg vec[2]=3 то есть если меньше 3 слов, то пользователь просто не ввел айди
            throw std::invalid_argument("No task id"); //invalid тип ошибки из стандартной библиотеки.Он означает:передан неправильный аргумент.
        }
        int TaskId = std::stoi(arg_vec[2]); //stoi превращает строку в число, например строку пользователя '3' мы делаем в 3.
        return DoneArguments{TaskId};
    }
    if (command=="add") {
        if (arg_quant<3) {
            throw std::invalid_argument("No task title");
        }
        std::string TaskTitle = arg_vec[2];
        return AddArguments{TaskTitle};
    }
    throw std::invalid_argument("Unknown command: "+ command);//если ни одно условие не подошло значит команда неизвестна
}

