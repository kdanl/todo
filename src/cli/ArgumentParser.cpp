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
    throw std::invalid_argument("Unknown command: "+ command);//если ни одно условие не подошло значит команда неизвестна
}

