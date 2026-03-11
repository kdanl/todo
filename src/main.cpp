#include "cli/ArgumentParser.hpp"
#include "utils/Terminal.hpp"
#include <exception>
#include <iostream>
#include <type_traits>
#include <variant>

int main(int arg_quant, char* arg_vec[]) { //argquant сколько аргументов передано, argvec сами аргументы
    try { //внутри этого блока может случиться ошибка (исключение),и тогда мы обработаем её в catch
        ArgumentParser parser; //Создаём объект parser класса ArgumentParser
        UnderstandCommand command = parser.parse(arg_quant,arg_vec);//просим разобрать то что написал пользователь и получаем variant с одной из комманд
        std::visit([](const auto& cmd){ //лямбда функция, cmd это текущая команда, но ее тип пока что неизвестен,поэтому визит поможет определить что это из HelpArgs, StatsArgs, ListArgs и т.д.
            using CmdType = std::decay_t<decltype(cmd)>; //decltype распознает тип cmd,decay очищает cmd от const &,
            if constexpr (std::is_same_v<CmdType,HelpArguments>) { //CmdType это тип известный только на этапе компиляции поэтому constexpr
                Terminal::print_help();
            }
            else if constexpr (std::is_same_v<CmdType,StatsArguments>) {
                std::cout<<"ДОБАВИТЬ ПОЗЖЕ\n";
            }
            else if constexpr (std::is_same_v<CmdType,ListArguments>) {
                std::cout<<"LIST command selected\n";
                if (cmd.ifDone) {
                    std::cout<<"filter: done tasks\n";
                }
                if (cmd.ifUndone) {
                    std::cout<<"filter: undone tasks\n";
                }
                if (cmd.priorityFilter) { //Проверяем, был ли указан фильтр по priority. это optional, сначала надо проверить,есть ли в нём значение
                    std::cout<<"priority filter = "<<*cmd.priorityFilter<<"\n";
                }
                if (cmd.sortFilter) { // Проверяем, был ли указан способ сортировки
                    std::cout<<"sort by = "<<*cmd.sortFilter<<"\n";
                }
            }
            else if constexpr (std::is_same_v<CmdType,DoneArguments>) {
                std::cout<<"DONE command selected, id = "<<cmd.id<<'\n';
            }
            else if constexpr (std::is_same_v<CmdType,AddArguments>) {
                std::cout<<"ADD command selected, title = "<<cmd.title<<'\n';
                if (cmd.priority) {
                    std::cout<<"priority = "<<*cmd.priority<<'\n';//разыменовываю optional
                }
                if (cmd.deadline) {
                    std::cout<<"deadline = "<<*cmd.deadline<<'\n';
                }
            }
            else if constexpr (std::is_same_v<CmdType,SearchArguments>) {
                std::cout<<"SEARCH command selected, name = "<<cmd.word<<'\n';
            }
        },command);//применить лямбда функцию к комманд
    } catch (const std::exception& err) {
        Terminal::print_error(err.what());
        return 1;//усли возвращаем 1 это обычно означает что программа завершилась с ошибкой
    }
    return 0; //если все норм возвращаем 0
}
