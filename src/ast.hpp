#ifndef AST_HPP
#define AST_HPP

#include "token.hpp"
#include <memory>
#include <any>

class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor
{
    public:
        virtual std::any visit(Binary const&) = 0;
        virtual std::any visit(Grouping const&) = 0;
        virtual std::any visit(Literal const&) = 0;
        virtual std::any visit(Unary const&) = 0;
};

class Expr
{
    public:
        Expr() = default;
        virtual ~Expr() = default;
        virtual std::any accept(Visitor* v) const
        {
            std::cerr << "Expr::accept() base function hit. Override it!\n"; 
            return std::any{};
        }
};

class Binary : public Expr
{
    template <typename T>
    using u_ptr = std::unique_ptr<T>;

    public:
        Binary(u_ptr<Expr> left, Token oper, u_ptr<Expr> right)
            : m_left{ std::move(left) }, m_operator{ oper }, m_right{ std::move(right) }
        {}

        std::any accept(Visitor* v) const override
        {
            return v->visit(*this);
        }

    public:
        u_ptr<Expr> m_left;
        Token   m_operator;
        u_ptr<Expr> m_right;
};

class Grouping : public Expr
{
    template <typename T>
    using u_ptr = std::unique_ptr<T>;

    public:
        Grouping(u_ptr<Expr> expr)
            :m_expression{ expr.release() }
        {}

        std::any accept(Visitor* v) const override
        {
            return v->visit(*this);
        }

    public:
        u_ptr<Expr>  m_expression;
};

class Literal : public Expr
{
    public:
        Literal(std::string obj)
            :m_value{ obj }
        {}

        std::any accept(Visitor* v) const override
        {
            return v->visit(*this);
        }

    public:
        std::string m_value;
};

class Unary : public Expr
{
    template <typename T>
    using u_ptr = std::unique_ptr<T>;

    public:
        Unary(Token oper, u_ptr<Expr> expr)
            : m_operator{ oper }, m_expression{ expr.release() }
        {}

        std::any accept(Visitor* v) const override
        {
            return v->visit(*this);
        }

    public:
        Token m_operator;
        u_ptr<Expr>  m_expression;
};

#endif // AST_HPP
