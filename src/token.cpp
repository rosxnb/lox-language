#include "token.hpp"

Token::Token(TokenType ttype, std::string lexeme, std::string literal, size_t line)
    : m_ttype(ttype), m_lexeme(lexeme), m_literal(literal), m_line(line)
{}

std::string Token::to_string() const
{
    return m_ttype + " " + m_lexeme + " " + m_literal;
}

std::string operator +(const TokenType token, const std::string& str)
{
    std::string str_token {};

    switch(token)
    {
        case TokenType::LEFT_PAREN:
            str_token = "TokenType::LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            str_token = "TokenType::RIGHT_PAREN";
            break;
        case TokenType::LEFT_BRACE:
            str_token = "TokenType::LEFT_BRACE";
            break;
        case TokenType::RIGHT_BRACE:
            str_token = "TokenType::RIGHT_BRACE";
            break;
        case TokenType::COMMA:
            str_token = "TokenType::COMMA";
            break;
        case TokenType::DOT:
            str_token = "TokenType::DOT";
            break;
        case TokenType::MINUS:
            str_token = "TokenType::MINUS";
            break;
        case TokenType::PLUS:
            str_token = "TokenType::PLUS";
            break;
        case TokenType::SEMICOLON:
            str_token = "TokenType::SEMICOLON";
            break;
        case TokenType::SLASH:
            str_token = "TokenType::SLASH";
            break;
        case TokenType::STAR:
            str_token = "TokenType::STAR";
            break;
        case TokenType::BANG:
            str_token = "TokenType::BANG";
            break;
        case TokenType::BANG_EQUAL:
            str_token = "TokenType::BANG_EQUAL";
            break;
        case TokenType::EQUAL:
            str_token = "TokenType::EQUAL";
            break;
        case TokenType::EQUAL_EQUAL:
            str_token = "TokenType::EQUAL_EQUAL";
            break;
        case TokenType::GREATER:
            str_token = "TokenType::GREATER";
            break;
        case TokenType::GREATER_EQUAL:
            str_token = "TokenType::GREATER_EQUAL";
            break;
        case TokenType::LESS:
            str_token = "TokenType::LESS";
            break;
        case TokenType::LESS_EQUAL:
            str_token = "TokenType::LESS_EQUAL";
            break;
        case TokenType::IDENTIFIER:
            str_token = "TokenType::IDENTIFIER";
            break;
        case TokenType::STRING:
            str_token = "TokenType::STRING";
            break;
        case TokenType::NUMBER:
            str_token = "TokenType::NUMBER";
            break;
        case TokenType::AND:
            str_token = "TokenType::AND";
            break;
        case TokenType::CLASS:
            str_token = "TokenType::CLASS";
            break;
        case TokenType::ELSE:
            str_token = "TokenType::ELSE";
            break;
        case TokenType::FALSE:
            str_token = "TokenType::FALSE";
            break;
        case TokenType::FUN:
            str_token = "TokenType::FUN";
            break;
        case TokenType::FOR:
            str_token = "TokenType::FOR";
            break;
        case TokenType::IF:
            str_token = "TokenType::IF";
            break;
        case TokenType::NIL:
            str_token = "TokenType::NIL";
            break;
        case TokenType::OR:
            str_token = "TokenType::OR";
            break;
        case TokenType::PRINT:
            str_token = "TokenType::PRINT";
            break;
        case TokenType::RETURN:
            str_token = "TokenType::RETURN";
            break;
        case TokenType::SUPER:
            str_token = "TokenType::SUPER";
            break;
        case TokenType::THIS:
            str_token = "TokenType::THIS";
            break;
        case TokenType::TRUE:
            str_token = "TokenType::TRUE";
            break;
        case TokenType::VAR:
            str_token = "TokenType::VAR";
            break;
        case TokenType::WHILE:
            str_token = "TokenType::WHILE";
            break;
        case TokenType::EOFT:
            str_token = "TokenType::EOFT";
            break;
        default: 
            return str;
    }

    return str_token + str;
}

std::ostream& operator <<(std::ostream& print, const Token& token)
{
    print << token.to_string();
    return print;
}
