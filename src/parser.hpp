#ifndef PARSER_HPP
#define PARSER_HPP


#include "token.hpp"
#include "ast.hpp"
#include <initializer_list>
#include <vector>
#include <memory>


// Recursive Descent parsing
class Parser
{
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T>
    using Vector = std::vector<T>;


    public:
        Parser(UniquePtr<Vector<Token>>);

    private:
        // expression → equality ;
        UniquePtr<Expr> expression();

        // equality → comparison ( ( "!=" | "==" ) comparison )* ;
        UniquePtr<Expr> equality();

        // comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
        UniquePtr<Expr> comparision();

        // term → factor ( ( "-" | "+" ) factor )* ;
        UniquePtr<Expr> term();

        // factor → unary ( ( "/" | "*" ) unary )* ;
        UniquePtr<Expr> factor();

        // unary → ( "!" | "-" ) unary | primary ;
        UniquePtr<Expr> unary();

        // primary → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
        UniquePtr<Expr> primary();

        Token advance();
        bool match(std::initializer_list<TokenType> const&);

        bool check(TokenType) const;
        bool is_end() const;
        Token peek() const;
        Token previous() const;


    private:
        UniquePtr<Vector<Token>> m_tokens;
        int m_current = 0;
};


#endif // PARSER_HPP

