//реализация ArgumentParser.hpp
#include "ArgumentParser.hpp"

#include <stdexcept>
#include <string>

UnderstandCommand ArgumentParser::parse(int arg_quant, char *arg_vec[]) const {
    if (arg_quant<2) {
        return HelpArguments{};
    }
    std::string command = arg_vec[1];
    if (command=="help") {
        return HelpArguments{};
    }
    if (command=="stats") {
        return StatsArguments{};
    }
    if (command=="list") {
        ListArguments ListArgs{};
        for (int i=2;i<arg_quant;i++) {
            std::string arg = arg_vec[i];
            if (arg == "--undone") {
                ListArgs.ifUndone=true;
            }
            else if (arg == "--done") {
                ListArgs.ifDone=true;
            }
            else if (arg == "--priority") {
                if (i+1>=arg_quant) {
                    throw std::invalid_argument("No value for --priority");
                }
                ListArgs.priorityFilter = arg_vec[i+1];
                i++;
            }
            else if (arg=="--sort") {
                if (i+1 >= arg_quant) {
                    throw std::invalid_argument("No value for --sort");
                }
                ListArgs.sortFilter=arg_vec[i+1];
                i++;
            }
            else {
                throw std::invalid_argument("Unknown flag: "+ arg);
            }
        }
        return ListArgs;
    }
    if (command=="done") {
        if (arg_quant<3) {
            throw std::invalid_argument("No task id");
        }
        int TaskId = std::stoi(arg_vec[2]);
        return DoneArguments{TaskId};
    }
    if (command=="add") {

        if (arg_quant<3) {
            throw std::invalid_argument("No task title");
        }

        std::string TaskTitle = arg_vec[2];

        std::optional<std::string> priority;
        std::optional<std::string> deadline;

        std::optional<std::string> repeat;
        std::optional<std::string> timeOfDay;

        for (int i=3;i<arg_quant;i++) {

            std::string arg = arg_vec[i];

            if (arg=="--priority") {

                if (i+1>=arg_quant) {
                    throw std::invalid_argument("No value for priority");
                }

                priority = arg_vec[i+1];
                i++;
            }

            else if (arg=="--deadline") {

                if (i+1>=arg_quant) {
                    throw std::invalid_argument("No value for deadline");
                }

                deadline = arg_vec[i+1];
                i++;
            }


            else if (arg=="--repeat") {

                if (i+1>=arg_quant) {
                    throw std::invalid_argument("No value for repeat");
                }

                repeat = arg_vec[i+1];
                i++;
            }

            else if (arg=="--time") {

                if (i+1>=arg_quant) {
                    throw std::invalid_argument("No value for time");
                }

                timeOfDay = arg_vec[i+1];
                i++;
            }

            else {
                throw std::invalid_argument("Unknown flag: " + arg);
            }
        }

        if (repeat && deadline) {
            throw std::invalid_argument("Cannot use --repeat with --deadline");
        }


        if (timeOfDay && !repeat) {
            throw std::invalid_argument("--time can only be used with --repeat");
        }

        if (repeat && !timeOfDay) {
            throw std::invalid_argument("--repeat requires --time");
        }

        return AddArguments{TaskTitle,priority,deadline,repeat,timeOfDay};
    }
    if (command=="search") {
        if (arg_quant<3) {
            throw std::invalid_argument("No value for search");
        }
        std::string FindWord = arg_vec[2];
        return SearchArguments{FindWord};
    }
    throw std::invalid_argument("Unknown command: "+ command);

}
