#pragma once//подключаем файл только один раз
#include <iostream>
#include <string>

namespace Terminal {

    constexpr const char* BRIGHT_CYAN = "\033[96m";
    constexpr const char* LIGHT_PINK = "\033[38;5;218m";
    constexpr const char* MAGENTA = "\033[95m";
    constexpr const char* BRIGHT_RED = "\033[91m";
    constexpr const char* LIGHT_GRAY = "\033[38;5;250m";
    constexpr const char* RESET = "\033[0m";

    inline void print_help() {
        std::cout<<BRIGHT_CYAN<<"Todo CLI\n"<<RESET;
        std::cout<<"\n";
        std::cout<<BRIGHT_CYAN<<"Commands:\n";
        std::cout<<LIGHT_PINK<<" add \"title\" [--priority low|medium|high] [--deadline YYYY-MM-DD]\n";
        std::cout<<LIGHT_PINK<<"add title [--repeat daily|weekly|monthly] [--time HH:MM]\n";
        std::cout<<LIGHT_PINK<<" list [--done] [--undone] [--priority LEVEL] [--sort priority|deadline]\n";
        std::cout<<LIGHT_PINK<<" search <word>\n";
        std::cout<<LIGHT_PINK<<" stats\n";
        std::cout<<LIGHT_PINK<<" help\n";
        std::cout<<"\n";
        std::cout <<BRIGHT_CYAN<< "Examples:\n";
        std::cout<<LIGHT_GRAY<< "  ./todo add \"Buy milk\"\n";
        std::cout<<LIGHT_GRAY<< "  ./todo add \"Homework\" --priority high\n";
        std::cout<<LIGHT_GRAY<< "  ./todo add \"Project\" --deadline 2026-03-10\n";
        std::cout<<LIGHT_GRAY<< "  ./todo list --done\n";
        std::cout<<LIGHT_GRAY<< "  ./todo list --priority high --sort priority\n";
        std::cout <<LIGHT_GRAY<< "  ./todo done 3\n";
        std::cout<<LIGHT_GRAY<< "  ./todo search milk\n";
    }
    inline void print_error(const std::string& error) {
        std::cerr<<BRIGHT_RED<<"Error: "<<error<<'\n';
    }
}