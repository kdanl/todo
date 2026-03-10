#pragma once
#include <iostream>
#include <string>

namespace Terminal {
    inline void print_help() {
        std::cout<<"Todo CLI\n";
        std::cout<<"Commands:\n";
        std::cout<<"add \"title\" [--priority low|medium|high] [--deadline YYYY-MM-DD]\n";
        std::cout<<"  list [--done] [--undone] [--priority LEVEL] [--sort priority|deadline]\n";
        std::cout<<" done <id>\n";
        std::cout<<" search <word>\n";
        std::cout<<" stats\n";
        std::cout<<" help\n";
    }
    inline void print_error(const std::string& error) {
        std::cerr<<"Error: "<<error<<'\n';
    }
}