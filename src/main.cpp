#include "cli/ArgumentParser.hpp"
#include "utils/Terminal.hpp"
#include "storage/JsonFileStorage.hpp" // дэниел
#include <exception>
#include <iostream>
#include <type_traits>
#include <variant>
#include "core/SimpleTask.hpp" // Anna
#include "core/DeadlineTask.hpp" // Anna
#include <memory>
#include <vector>

int main(int arg_quant, char* arg_vec[]) { //argquant сколько аргументов передано, argvec сами аргументы
    try { //внутри этого блока может случиться ошибка (исключение),и тогда мы обработаем её в catch
        ArgumentParser parser; //Создаём объект parser класса ArgumentParser
        JsonFileStorage fileStorage; // дэниел
        TaskStorage storage;

        storage.setTasks(fileStorage.load()); // дэниел

        UnderstandCommand command = parser.parse(arg_quant,arg_vec);//просим разобрать то что написал пользователь и получаем variant с одной из комманд

        std::visit([&storage](const auto& cmd){ //лямбда функция, cmd это текущая команда, но ее тип пока что неизвестен,поэтому визит поможет определить что это из HelpArgs, StatsArgs, ListArgs и т.д.

            using CmdType = std::decay_t<decltype(cmd)>; //decltype распознает тип cmd,decay очищает cmd от const &,

            if constexpr (std::is_same_v<CmdType,HelpArguments>) { //CmdType это тип известный только на этапе компиляции поэтому constexpr
                Terminal::print_help();
            }
            else if constexpr (std::is_same_v<CmdType,StatsArguments>) { // Anna

                int total = storage.getTaskCount();
                int completed = storage.getCompletedCount();
                auto percent = storage.getProgressPercentage();

                std::cout << Terminal::MAGENTA << "STATS" << Terminal::RESET
                          << " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "total tasks = " << Terminal::RESET
                          << total << "\n";

                std::cout << Terminal::BRIGHT_CYAN << "completed tasks = " << Terminal::RESET
                          << completed << "\n";

                if (percent.has_value()) {
                    std::cout << Terminal::BRIGHT_CYAN << "progress = " << Terminal::RESET
                              << completed << "/" << total << " (" << percent.value() << "%)\n";
                } else {
                    std::cout << Terminal::BRIGHT_CYAN << "progress = " << Terminal::RESET
                              << "No tasks yet\n";
                }
            }

            else if constexpr (std::is_same_v<CmdType,ListArguments>) { //Anna

                std::cout << Terminal::MAGENTA << "LIST" << Terminal::RESET
                          << " command selected\n";

                if (cmd.sort) {
                    storage.sortByPriority();
                }

                const auto& tasks = storage.getTasks();

                for (const auto& task : tasks) {

                    if (cmd.ifDone && !task->isComplete()) {
                        continue;
                    }

                    if (cmd.ifUndone && task->isComplete()) {
                        continue;
                    }

                    std::cout << task->toString() << "\n";
                }
            }

            else if constexpr (std::is_same_v<CmdType,DoneArguments>) { //Anna

                Task* task = storage.findById(cmd.id);

                if (!task) {
                    throw std::invalid_argument("Task not found");
                }

                task->markDone();

                std::cout << Terminal::MAGENTA << "DONE" << Terminal::RESET
                          << " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "id = " << Terminal::RESET
                          << cmd.id << '\n';
            }

            else if constexpr (std::is_same_v<CmdType,AddArguments>) { //Anna

                int newId = storage.getTaskCount() + 1;
                Priority p = Priority::Low;

                if (cmd.priority) {
                    p = priorityFromString(*cmd.priority);
                }

                if (cmd.deadline) {
                    storage.addTask(std::make_unique<DeadlineTask>(newId, cmd.title, *cmd.deadline, p));
                }
                else {
                    storage.addTask(std::make_unique<SimpleTask>(newId, cmd.title, p));
                }

                std::cout << Terminal::MAGENTA << "ADD" << Terminal::RESET
                          << " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "title = " << Terminal::RESET
                          << cmd.title << '\n';

                if (cmd.deadline) {
                    std::cout << Terminal::BRIGHT_CYAN << "deadline = " << Terminal::RESET
                              << *cmd.deadline << '\n';
                }
            }

            else if constexpr (std::is_same_v<CmdType,SearchArguments>) { //Anna

                std::cout << Terminal::MAGENTA << "SEARCH" << Terminal::RESET
                          << " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "word = " << Terminal::RESET
                          << cmd.word << '\n';

                std::vector<Task*> results = storage.findByTitle(cmd.word);

                for (Task* task : results) {
                    std::cout << task->toString() << "\n";
                }
            }

        },command); //применить лямбда функцию к комманд

        fileStorage.save(storage.getTasks()); // дэниел

    } catch (const std::exception& err) {
        Terminal::print_error(err.what());
        return 1;//усли возвращаем 1 это обычно означает что программа завершилась с ошибкой
    }

    return 0; //если все норм возвращаем 0
}