#pragma once
#include <boost/any.hpp>
#include <memory>
#include <vector>
#include "Tokens.h"
#include "Interpreter.h"
#include "Scanner.h"
#include "Literals.h"
#include "Visitor.h"


namespace Lox {
    namespace Interpreter {

        template<typename R> class Visitor;
            /// <summary>
            /// 
            /// </summary>
            class Expr {
            public:
                virtual ~Expr() = default;

                // TODO: template visitors?
                virtual boost::any accept(Visitor<boost::any>& visitor) const = 0;
            };

            /// <summary>
            /// 
            /// </summary>
            class BinaryExpr : public Expr {

            public:
                BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
                boost::any accept(Visitor<boost::any>& visitor) const override;

                const Expr& getLeftExpr() const { return *lExpr; }
                const Token getOp() const { return op; }
                const Expr& getRightExpr() const { return *rExpr; }

            private:

                std::unique_ptr<Expr> lExpr;
                Token op;
                std::unique_ptr<Expr> rExpr;
            };

            /// <summary>
            /// 
            /// </summary>
            class GroupingExpr : public Expr {
            public:
                GroupingExpr(std::unique_ptr<Expr> expr);
                boost::any accept(Visitor<boost::any>& visitor) const override;

                const Expr& getExpr() const { return *expr; }

            private:
                std::unique_ptr<Expr> expr;
            };

            /// <summary>
            /// 
            /// </summary>
            class LiteralExpr : public Expr {
            public:
                LiteralExpr(std::unique_ptr<Literal> lit);
                boost::any accept(Visitor<boost::any>& visitor) const override;

                const Literal& getLiteral() const { return *literal; } // get reference of the literal

            private:

                std::unique_ptr<Literal> literal;

            };

            /// <summary>
            /// 
            /// </summary>
            class UnaryExpr : public Expr {
            public:
                UnaryExpr(Token op, std::unique_ptr<Expr> rExpr);
                boost::any accept(Visitor<boost::any>& visitor) const override;

                const Token getOp() const { return op; }
                const Expr& getRightExpr() const { return *rExpr; };

            private:
                Token op;
                std::unique_ptr<Expr> rExpr; 
            };

            class VariableExpr : public Expr {
            public:
                VariableExpr(Token name);
                boost::any accept(Visitor<boost::any>& visitor) const override;

                const Token getVar() const { return name; }

            private:
                Token name;
            };

            class AssignExpr : public Expr {
            public:
                AssignExpr(Token name, std::unique_ptr<Expr> value);
                boost::any accept(Visitor<boost::any>& visitor) const override;

                const Token getName() const { return name; }
                const Expr& getValue() const { return *value; }

            private:
                Token name;
                std::unique_ptr<Expr> value;

            };
    }
}