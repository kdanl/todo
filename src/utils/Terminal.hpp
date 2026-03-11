#pragma once//подключаем файл только один раз
#include <iostream>
#include <string>

namespace Terminal { //группирую все функции  связанные с выводом в терминал
    inline void print_help() { //печатает справку по программе
        std::cout<<"Todo CLI\n"; //печатает название программы
        std::cout<<"\n";
        std::cout<<"Commands:\n"; //заголовок списка комманд
        std::cout<<"\n";
        std::cout<<"add \"title\" [--priority low|medium|high] [--deadline YYYY-MM-DD]\n";
        std::cout<<"\n";
        std::cout<<"  list [--done] [--undone] [--priority LEVEL] [--sort priority|deadline]\n";
        std::cout<<"\n";
        std::cout<<" done <id>\n";
        std::cout<<"\n";
        std::cout<<" search <word>\n";
        std::cout<<"\n";
        std::cout<<" stats\n";
        std::cout<<"\n";
        std::cout<<" help\n";
        std::cout<<"\n";
        std::cout << "Examples:\n";// Заголовок с примерами использования.
        std::cout << "  ./todo add \"Buy milk\"\n";
        std::cout << "  ./todo add \"Homework\" --priority high\n";
        std::cout << "  ./todo add \"Project\" --deadline 2026-03-10\n";
        std::cout << "  ./todo list --done\n";
        std::cout << "  ./todo list --priority high --sort deadline\n";
        std::cout << "  ./todo done 3\n";
        std::cout << "  ./todo search milk\n";
    }
    inline void print_error(const std::string& error) {
        std::cerr<<"Error: "<<error<<'\n';
    }
}