#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "ast.hpp"
#include "token.hpp"
#include <initializer_list>
#include <memory>
#include <sstream>

class AstPrinter : public Visitor
{
    template <typename p>
    using u_ptr = std::unique_ptr<p>;

    public:
        void run()
        {
            std::unique_ptr<Expr> expression = std::make_unique<Binary>(
                std::make_unique<Unary>(Token(TokenType::MINUS, "-", ""), std::make_unique<Literal>("123")),
                Token(TokenType::STAR, "*", ""),
                std::make_unique<Grouping>(std::make_unique<Literal>("45.67"))
            );

            std::cout << std::any_cast<std::string>(expression->accept(this)) << "\n";
        }

        std::any visit(Binary const& expr) override
        {
            return std::string(parenthesize(expr.m_operator.m_lexeme, {expr.m_left.get(), expr.m_right.get()}));
        }

        std::any visit(Grouping const& expr) override
        {
            return std::string(parenthesize("group", {expr.m_expression.get()}));
        }

        std::any visit(Literal const& expr) override
        {
            if (expr.m_value.empty())
                return "nil";
            return expr.m_value;
        }

        std::any visit(Unary const& expr) override
        {
            return std::string(parenthesize(expr.m_operator.m_lexeme, {expr.m_expression.get()}));
        }

    private:
        std::string parenthesize(std::string name, std::initializer_list<Expr*> exprs)
        {
            std::stringstream ss;

            ss << '(' << name;
            for (auto const& expr: exprs)
            {
                if (!expr) continue;
                ss << ' ';
                ss << std::any_cast<std::string>(expr->accept(this));
            }
            ss << ')';

            return ss.str();
        }
};

#endif // AST_PRINTER_HPP
