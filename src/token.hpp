#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <any>
#include <sstream>

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
        Token(TokenType ttype, std::string lexeme, std::any literal);
        std::string to_string() const;
        static std::string any_to_str(std::any const&);
        friend std::ostream& operator <<(std::ostream& print, const Token& token);

    public:
        TokenType           m_ttype;
        std::string         m_lexeme;
        std::any            m_literal;

};

#endif // TOKEN_HPP
