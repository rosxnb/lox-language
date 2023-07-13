#include "scanner.hpp"
#include "lox.hpp"

Scanner::Scanner(const std::string& source)
    : m_source(source)
{}

std::vector<Token> Scanner::generate_tokens()
{
    while (!is_end()) {
        m_start = m_current;
        scan_token();
    }

    m_tokens.emplace_back( TokenType::EOFT, "", "", m_line );
    return m_tokens;
}

void Scanner::scan_token()
{
    char c = advance();
    switch(c) {
        case '(': add_token(TokenType::LEFT_PAREN); break;
        case ')': add_token(TokenType::RIGHT_PAREN); break;
        case '{': add_token(TokenType::LEFT_BRACE); break;
        case '}': add_token(TokenType::RIGHT_BRACE); break;
        case ',': add_token(TokenType::COMMA); break;
        case '.': add_token(TokenType::DOT); break;
        case '-': add_token(TokenType::MINUS); break;
        case '+': add_token(TokenType::PLUS); break;
        case ';': add_token(TokenType::SEMICOLON); break;
        case '*': add_token(TokenType::STAR); break;
        case '!':
            add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            add_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !is_end())
                    advance();
            } else {
                add_token(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\t':
        case '\r': break;
        case '\n': m_line++; break;
        default:
            if (is_digit(c)) {
                consume_number();
            } else if (is_alpha(c)) {
                consume_identifier();
            } else {
                Lox::error(m_line, "unexpected character.");
            }
    }
}

void Scanner::add_token(TokenType type, std::string literal)
{
    std::string text = m_source.substr(m_start, m_current);
    m_tokens.emplace_back( type, text, literal, m_line );
}

char Scanner::advance()
{
    m_current++;
    return m_source[m_current - 1];
}

bool Scanner::match(char expected)
{
    if (is_end())
        return false;
    if (m_source[m_current] != expected)
        return false;

    m_current++;
    return true;
}

void Scanner::consume_number()
{
    while (is_digit(peek()))
        advance();

    if (peek() == '.' && is_digit(peek_next())) {
        advance();
        while (is_digit(peek()))
            advance();
    }

    add_token(TokenType::NUMBER, m_source.substr(m_start, m_current));
}

void Scanner::consume_identifier()
{
    while (is_alpha_numeric(peek()))
        advance();

    // check if it is reserved keyword
    std::string text = m_source.substr(m_start, m_current);
    TokenType type   = 
        keywords.find(text) != keywords.end() ?
        keywords[text] : TokenType::IDENTIFIER;

    add_token(type);
}

void Scanner::string()
{
    while (peek() != '"' && !is_end()) {
        if (peek() == '\n') m_line++;
        advance();
    }

    if (is_end()) {
        Lox::error(m_line, "unterminated string.");
        return;
    }

    advance();

    std::string value = m_source.substr(m_start + 1, m_current);
    add_token(TokenType::STRING, value);
}

char Scanner::peek() const
{
    if (is_end()) 
        return '\0';
    return m_source[m_current];
}

char Scanner::peek_next() const
{
    if (m_current + 1 >= m_source.length())
        return '\0';
    return m_source[m_current + 1];
}

bool Scanner::is_end() const
{
    return m_current >= m_source.length();
}

bool Scanner::is_digit(char c) const
{
    return c >= '0' || c <= '9';
}

bool Scanner::is_alpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool Scanner::is_alpha_numeric(char c) const
{
    return is_alpha(c) || is_digit(c);
}

std::unordered_map<std::string, TokenType> Scanner::keywords = {
    {"and", TokenType::AND},
    {"class", TokenType::AND},
    {"else", TokenType::AND},
    {"false", TokenType::AND},
    {"for", TokenType::AND},
    {"fun", TokenType::AND},
    {"if", TokenType::AND},
    {"nil", TokenType::AND},
    {"or", TokenType::AND},
    {"print", TokenType::AND},
    {"return", TokenType::AND},
    {"super", TokenType::AND},
    {"this", TokenType::AND},
    {"true", TokenType::AND},
    {"var", TokenType::AND},
    {"while", TokenType::AND},
};
