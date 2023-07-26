#include <iostream>
#include "lox.hpp"
#include "ast_printer.hpp"

int main(int argc, char** argv)
{
    // AstPrinter obj;
    // obj.run();
    // return 0;

    if (argc > 2) {
        std::cerr << "Useage:\n"
                  << "  lox [file]\n"
                  << "  lox\n";
        return -1;
    } 

    Lox lox;
    argc == 2 ? lox.run_file(argv[1]) : lox.run_repl();

    return 0;
}
