#include "parser.hpp"

Parser::Parser(std::unique_ptr<std::vector<Token>> tokens)
    : m_tokens{ std::move(tokens) }
{}

// expression → equality ;
std::unique_ptr<Expr> Parser::expression()
{
    return equality();
}

// equality → comparison ( ( "!=" | "==" ) comparison )* ;
std::unique_ptr<Expr> Parser::equality()
{
    std::unique_ptr<Expr> expr = comparision();

    while ( match({TokenType::BANG_EQUAL, TokenType::EQUAL}) )
    {
        Token oper = previous();
        std::unique_ptr<Expr> right = comparision();
        std::unique_ptr<Expr> nExpr = std::make_unique<Binary>(std::move(expr), oper, std::move(right));
        expr = std::move(nExpr);
    }

    return expr;
}

// comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
std::unique_ptr<Expr> Parser::comparision()
{
    std::unique_ptr<Expr> expr = term();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL}))
    {
        Token oper = previous();
        std::unique_ptr<Expr> right = term();
        std::unique_ptr<Expr> nExpr = std::make_unique<Binary>(std::move(expr), oper, std::move(right));
        expr = std::move(nExpr);
    }

    return expr;
}

// term → factor ( ( "-" | "+" ) factor )* ;
std::unique_ptr<Expr> Parser::term()
{
    std::unique_ptr<Expr> expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS}))
    {
        Token oper = previous();
        std::unique_ptr<Expr> right = factor();
        std::unique_ptr<Expr> nExpr = std::make_unique<Binary>(std::move(expr), oper, std::move(right));
        expr = std::move(nExpr);
    }

    return expr;
}

// factor → unary ( ( "/" | "*" ) unary )* ;
std::unique_ptr<Expr> Parser::factor()
{
    std::unique_ptr<Expr> expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR}))
    {
        Token oper = previous();
        std::unique_ptr<Expr> right = unary();
        std::unique_ptr<Expr> nExpr = std::make_unique<Binary>(std::move(expr), oper, std::move(right));
        expr = std::move(nExpr);
    }

    return expr;
}

// unary → ( "!" | "-" ) unary | primary ;
std::unique_ptr<Expr> Parser::unary()
{
    if (match({TokenType::BANG, TokenType::MINUS}))
    {
        Token oper = previous();
        std::unique_ptr<Expr> right = unary();
        return std::make_unique<Unary>(oper, std::move(right));
    }

    return primary();
}

// primary → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
std::unique_ptr<Expr> Parser::primary()
{
    if (match({TokenType::FALSE}))
        return std::make_unique<Literal>(false);

    if (match({TokenType::TRUE}))
        return std::make_unique<Literal>(true);

    if (match({TokenType::NIL}))
        return std::make_unique<Literal>(NULL);

    if (match({TokenType::NUMBER, TokenType::STRING}))
        return std::make_unique<Literal>(previous().m_literal);

    if (match({TokenType::LEFT_PAREN}))
    {
        std::unique_ptr<Expr> expr = expression();
        // consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<Grouping>(std::move(expr));
    }

    return nullptr;
}

bool Parser::match(std::initializer_list<TokenType> const& types)
{
    for (TokenType const& type: types)
        if (check(type))
        {
            advance();
            return true;
        }

    return false;
}

bool Parser::check(TokenType type) const
{
    if (is_end())
        return false;

    return peek().m_ttype == type;
}

Token Parser::advance()
{
    if (!is_end())
        m_current++;
    return previous();
}

bool Parser::is_end() const
{
    return peek().m_ttype == TokenType::EOFT;
}

Token Parser::peek() const
{
    return m_tokens->at(m_current);
}

Token Parser::previous() const
{
    return m_tokens->at(m_current - 1);
}
