#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "ast.hpp"
#include "token.hpp"
#include <sstream>

class AstPrinter : public Visitor
{
    template <typename p>
    using u_ptr = std::unique_ptr<p>;

    public:
        void run()
        {
            std::unique_ptr<Expr> expression = std::make_unique<Binary>(
                std::make_unique<Unary>(Token(TokenType::MINUS, "-", {}), std::make_unique<Literal>(123.)),
                Token(TokenType::STAR, "*", {}),
                std::make_unique<Grouping>(std::make_unique<Literal>(45.67))
            );

            std::cout << std::any_cast<std::string>(expression->accept(this)) << "\n";
        }

        std::any visit(Binary const& expr) override
        {
            return parenthesize(expr.m_operator.m_lexeme, {expr.m_left.get(), expr.m_right.get()});
        }

        std::any visit(Grouping const& expr) override
        {
            return parenthesize("group", {expr.m_expression.get()});
        }

        std::any visit(Literal const& expr) override
        {
            if (!expr.m_value.has_value())
                return "nil";
            return expr.m_value;
        }

        std::any visit(Unary const& expr) override
        {
            return parenthesize(expr.m_operator.m_lexeme, {expr.m_expression.get()});
        }

    private:
        std::any parenthesize(std::string name, std::initializer_list<Expr*> exprs)
        {
            std::stringstream ss;

            ss << '(' << name;
            for (auto const& expr: exprs)
            {
                ss << ' ';

                std::any result = expr->accept(this);
                // std::cout << result.type().name() << std::endl;

                if ( result.type() == typeid(std::string) )
                    ss << std::any_cast<std::string>(result);
                else if ( result.type() == typeid(const char*) )
                    ss << std::any_cast<const char*>(result);
                else
                // ( result.type() == typeid(double) || result.type() == typeid(float) || 
                //   result.type() == typeid(int) || result.type() == typeid(long) )
                    ss << std::any_cast<double>(result);
            }
            ss << ')';

            return ss.str();
        }
};

#endif // AST_PRINTER_HPP
