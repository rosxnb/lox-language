#include <fstream>
#include <sstream>
#include <iostream>

#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"

bool Lox::had_error = false;

void Lox::report(int line, const std::string& where, const std::string& message)
{
    std::cerr << "error: [line " << line << "] " << where << " \n\t" << message << "\n";
}

void Lox::error(int line, const std::string& message)
{
    had_error = true;
    report(line, "", message);
}

void Lox::run_file(std::string_view filepath) const
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string source;
    try {
        file.open(filepath);
        std::stringstream ss;
        ss << file.rdbuf();
        source = ss.str();
    } catch (std::ifstream::failure ex) {
        std::cerr << "Failed to open file: " << filepath;
        std::cerr << "\n  " << ex.what() << "\n";
    }

    run(source);
    if (had_error) exit(-1);
}

void Lox::run_repl() const
{
    print_version();
    std::cout << "Welcome to Lox REPL\n\n";

    std::string prompt_symbol { ">>> " };
    std::string prompt;

    std::cout << prompt_symbol;
    while (std::getline(std::cin, prompt)) {
        run(prompt);
        had_error = false;
        std::cout << prompt_symbol;
    }

    std::cout << "\n"; return;
}

void Lox::run(const std::string& source) const
{
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.generate_tokens();

    for (const auto& token: tokens)
        std::cout << token << "\n";
}

void Lox::print_version() const
{
    std::cout << "Lox interpreter 2023\n"
              << "Version 1.0.0\n";
}
