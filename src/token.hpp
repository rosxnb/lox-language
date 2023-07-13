#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

enum class TokenType
{
    // single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // one or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // literals
    IDENTIFIER, STRING, NUMBER,

    // keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOFT,
};

std::string operator +(const TokenType token, const std::string& str);


class Token
{
    public:
        Token(TokenType ttype, std::string lexeme, std::string literal, size_t line);
        std::string to_string() const;
        friend std::ostream& operator <<(std::ostream& print, const Token& token);

    private:
        TokenType           m_ttype;
        std::string         m_lexeme;
        std::string         m_literal;
        size_t              m_line;
};

#endif // TOKEN_HPP
