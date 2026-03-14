#include "cli/ArgumentParser.hpp"
#include "utils/Terminal.hpp"
#include "storage/JsonFileStorage.hpp" // дэниел

#include "core/SimpleTask.hpp" // Anna
#include "core/DeadlineTask.hpp" //Elina
#include "core/RepeatingTask.hpp"//Anna
#include "core/TaskStorage.hpp"//Anna

#include <exception>
#include <iostream>
#include <type_traits>
#include <variant>




int main(int arg_quant, char* arg_vec[]) {
    try {
        ArgumentParser parser;
        JsonFileStorage fileStorage; //Daniel
        TaskStorage storage;//Anna

        auto tasks = fileStorage.load();//Anna


        for (auto& t : tasks) {//Anna
            storage.addTask(std::move(t));//Anna
        }
        storage.updateRepeatingTasks(); //Anna

        storage.updateRepeatingTasks();//Anna
        UnderstandCommand command = parser.parse(arg_quant,arg_vec);

        std::visit([&storage](const auto& cmd){

            using CmdType = std::decay_t<decltype(cmd)>; //decltype распознает тип cmd,decay очищает cmd от const &,

            if constexpr (std::is_same_v<CmdType,HelpArguments>) {
                Terminal::print_help();
            }
            else if constexpr (std::is_same_v<CmdType,StatsArguments>) {

                int total = storage.getTaskCount();//Anna
                int completed = storage.getCompletedCount();//Anna
                auto percent = storage.getProgressPercentage();//Anna

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

            else if constexpr (std::is_same_v<CmdType,ListArguments>) {

                std::cout << Terminal::MAGENTA << "LIST" << Terminal::RESET
                          << " command selected\n";

                if (cmd.sortFilter) {//Anna
                    storage.sortByPriority();//Anna
                }

                const auto& tasks = storage.getTasks();//Anna

                for (const auto& task : tasks) {//Anna

                    if (cmd.ifDone && !task->isComplete()) {//Anna
                        continue;//Anna
                    }

                    if (cmd.ifUndone && task->isComplete()) {//Anna
                        continue;//Anna
                    }

                    std::cout << task->toString() << "\n";//Anna
                }
            }

            else if constexpr (std::is_same_v<CmdType,DoneArguments>) { //Elina

                Task* task = storage.findById(cmd.id);//Anna

                if (!task) {//Elina
                    throw std::invalid_argument("Task not found");//Elina
                }

                task->markDone();//Anna

                std::cout << Terminal::MAGENTA << "DONE" << Terminal::RESET<< " command selected\n";//Elina

                std::cout << Terminal::BRIGHT_CYAN << "id = " << Terminal::RESET<< cmd.id << '\n';//Elina
            }

            else if constexpr (std::is_same_v<CmdType,AddArguments>) { //Elina

                int newId = storage.getTaskCount() + 1;//Anna
                Priority p = Priority::Low;//Anna

                if (cmd.priority) {//Elina
                    p = priorityFromString(*cmd.priority);//Anna
                }

                if (cmd.repeat) {//Elina

                    storage.addTask(//Anna
                        std::make_unique<RepeatingTask>(//Anna
                            newId,//Anna
                            cmd.title,//Anna
                            *cmd.repeat,//Anna
                            *cmd.timeOfDay,//Anna
                            p//Anna
                        )
                    );
                }

                else if (cmd.deadline) {//Elina

                    storage.addTask(//Anna
                        std::make_unique<DeadlineTask>(//Anna
                            newId,//Anna
                            cmd.title,//Anna
                            *cmd.deadline,//Anna
                            p//Anna
                        )
                    );
                }

                else {

                    storage.addTask(//Anna
                        std::make_unique<SimpleTask>(//Anna
                            newId,//Anna
                            cmd.title,//Anna
                            p//Anna
                        )
                    );
                }

                std::cout << Terminal::MAGENTA << "ADD" << Terminal::RESET<< " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "title = " << Terminal::RESET<< cmd.title << '\n';

                if (cmd.deadline) {//Elina
                    std::cout << Terminal::BRIGHT_CYAN << "deadline = " << Terminal::RESET
                              << *cmd.deadline << '\n';
                }
            }

            else if constexpr (std::is_same_v<CmdType,SearchArguments>) { //Elina

                std::cout << Terminal::MAGENTA << "SEARCH" << Terminal::RESET
                          << " command selected\n";

                std::cout << Terminal::BRIGHT_CYAN << "word = " << Terminal::RESET
                          << cmd.word << '\n';

                std::vector<Task*> results = storage.findByTitle(cmd.word);// Anna

                for (Task* task : results) {// Anna
                std::shared_ptr<Task> view(task, [](Task*){}); // Anna
                std::cout << view->toString() << "\n";// Anna
                }
            }

        },command);

        fileStorage.save(storage.getTasks()); //Daniel

    } catch (const std::exception& err) {//Elina
        Terminal::print_error(err.what());//Elina
        return 1;
    }

    return 0;
}