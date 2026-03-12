#include "cli/ArgumentParser.hpp"
#include "utils/Terminal.hpp"
#include <exception>
#include <iostream>
#include <type_traits>
#include <variant>
#include "core/TaskStorage.hpp"

int main(int arg_quant, char* arg_vec[]) { //argquant сколько аргументов передано, argvec сами аргументы
    try { //внутри этого блока может случиться ошибка (исключение),и тогда мы обработаем её в catch
        ArgumentParser parser; //Создаём объект parser класса ArgumentParser
        TaskStorage storage;
        UnderstandCommand command = parser.parse(arg_quant,arg_vec);//просим разобрать то что написал пользователь и получаем variant с одной из комманд

        std::visit([&storage](const auto& cmd){ //лямбда функция, cmd это текущая команда, но ее тип пока что неизвестен,поэтому визит поможет определить что это из HelpArgs, StatsArgs, ListArgs и т.д.

            using CmdType = std::decay_t<decltype(cmd)>; //decltype распознает тип cmd,decay очищает cmd от const &,

            if constexpr (std::is_same_v<CmdType,HelpArguments>) { //CmdType это тип известный только на этапе компиляции поэтому constexpr
                Terminal::print_help();
            }

            else if constexpr (std::is_same_v<CmdType,StatsArguments>) {
                int total = storage.getTaskCount();
                int completed = storage.getCompletedCount();
                int percent = storage.getProgressPercentage();

                std::cout << Terminal::MAGENTA << "STATS" << Terminal::RESET << " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "total tasks = " << Terminal::RESET<< total << "\n";

                std::cout << Terminal::BRIGHT_CYAN << "completed tasks = " << Terminal::RESET<< completed << "\n";

                std::cout << Terminal::BRIGHT_CYAN << "progress = " << Terminal::RESET<< completed << "/" << total << " (" << percent << "%)\n";
            }

            else if constexpr (std::is_same_v<CmdType,ListArguments>) {

                std::cout << Terminal::MAGENTA << "LIST" << Terminal::RESET<< " command selected\n";

                if (cmd.ifDone) {
                    std::cout << Terminal::BRIGHT_CYAN << "filter = " << Terminal::RESET<< "done tasks\n";
                }

                if (cmd.ifUndone) {
                    std::cout << Terminal::BRIGHT_CYAN << "filter = " << Terminal::RESET<< "undone tasks\n";
                }

                if (cmd.priorityFilter) { //Проверяем, был ли указан фильтр по priority. это optional, сначала надо проверить,есть ли в нём значение
                    std::cout << Terminal::BRIGHT_CYAN << "priority filter = " << Terminal::RESET<< *cmd.priorityFilter << "\n";
                }

                if (cmd.sortFilter) { // Проверяем, был ли указан способ сортировки
                    std::cout << Terminal::BRIGHT_CYAN << "sort by = " << Terminal::RESET<< *cmd.sortFilter << "\n";
                }
            }

            else if constexpr (std::is_same_v<CmdType,DoneArguments>) {

                std::cout << Terminal::MAGENTA << "DONE" << Terminal::RESET<< " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "id = " << Terminal::RESET<< cmd.id << '\n';
            }

            else if constexpr (std::is_same_v<CmdType,AddArguments>) {

                std::cout << Terminal::MAGENTA << "ADD" << Terminal::RESET<< " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "title = " << Terminal::RESET<< cmd.title << '\n';

                if (cmd.priority) {

                    if (*cmd.priority=="high") {
                        std::cout << Terminal::BRIGHT_CYAN << "priority = " << Terminal::RESET<< Terminal::RED << *cmd.priority << Terminal::RESET << "\n";
                    }

                    else if (*cmd.priority=="medium") {
                        std::cout << Terminal::BRIGHT_CYAN << "priority = " << Terminal::RESET<< Terminal::YELLOW << *cmd.priority << Terminal::RESET << "\n";
                    }

                    else if (*cmd.priority=="low") {
                        std::cout << Terminal::BRIGHT_CYAN << "priority = " << Terminal::RESET<< Terminal::GREEN << *cmd.priority << Terminal::RESET << "\n";
                    }

                    else {
                        std::cout << Terminal::BRIGHT_CYAN << "priority = " << Terminal::RESET<< *cmd.priority << "\n";
                    }
                }

                if (cmd.deadline) {
                    std::cout << Terminal::BRIGHT_CYAN << "deadline = " << Terminal::RESET<< *cmd.deadline << '\n';
                }
            }

            else if constexpr (std::is_same_v<CmdType,SearchArguments>) {

                std::cout << Terminal::MAGENTA << "SEARCH" << Terminal::RESET<< " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "word = " << Terminal::RESET<< cmd.word << '\n';
            }

        },command); //применить лямбда функцию к комманд

    } catch (const std::exception& err) {
        Terminal::print_error(err.what());
        return 1;//усли возвращаем 1 это обычно означает что программа завершилась с ошибкой
    }

    return 0; //если все норм возвращаем 0
}
