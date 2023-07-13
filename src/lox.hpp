#ifndef LOX_HPP
#define LOX_HPP

#include <string>

class Lox
{
    public:
        static void error(int line, const std::string& message);
        static void report(int line, const std::string& where, const std::string& message);

        void run_file(std::string_view filepath) const;
        void run_repl() const;

    private:
        void run(const std::string& source) const;
        void print_version() const;

    private:
        static bool had_error;
};

#endif // LOX_HPP
