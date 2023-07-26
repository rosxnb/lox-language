#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <unordered_map>
#include "token.hpp"

class Scanner
{
    public:
        Scanner(const std::string& source);
        std::vector<Token> generate_tokens();

    private:
        void scan_token();
        bool match(char);
        void consume_number();
        void consume_identifier();
        char advance();
        void add_token(TokenType, std::any = {});
        void consume_string();
        void consume_block_comment();
        char peek() const;
        char peek_next() const;
        bool is_end() const;
        bool is_digit(char) const;
        bool is_alpha(char) const;
        bool is_alpha_numeric(char) const;


    private:
        std::string             m_source;
        int                     m_start = 0;
        int                     m_current = 0;
        int                     m_line = 1;
        std::vector<Token>      m_tokens;
        static std::unordered_map<std::string, TokenType> keywords;
};

#endif // SCANNER_HPP
