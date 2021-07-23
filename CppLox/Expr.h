#pragma once
#include <boost/any.hpp>
#include <memory>

#include "Tokens.h"
#include "Interpreter.h"
#include "Scanner.h"
#include "Literals.h"
#include "Visitor.h"


namespace Lox {
    namespace Interpreter {


        class Visitor;
            /// <summary>
            /// 
            /// </summary>
            class Expr {
            public:
                virtual ~Expr() = default;

                // TODO: template visitors?
                virtual void accept(Visitor& visitor) = 0;
            };

            /// <summary>
            /// 
            /// </summary>
            class BinaryExpr : public Expr {

            public:
                BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
                void accept(Visitor& visitor);

                std::unique_ptr<Expr> getLeftExpr() { return std::move(lExpr); }
                const Token getOp() const { return op; }
                std::unique_ptr<Expr> getRightExpr() { return std::move(rExpr); }

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
                void accept(Visitor& visitor);

                std::unique_ptr<Expr> getExpr() { return std::move(expr); }

            private:
                std::unique_ptr<Expr> expr;
            };

            /// <summary>
            /// 
            /// </summary>
            class LiteralExpr : public Expr {
            public:
                LiteralExpr(std::unique_ptr<Literal> lit);
                void accept(Visitor& visitor);

                Literal* getLiteral() { return literal.get(); } // get copy of the literal

            private:

                std::unique_ptr<Literal> literal;

            };

            /// <summary>
            /// 
            /// </summary>
            class UnaryExpr : public Expr {
            public:
                UnaryExpr(Token op, std::unique_ptr<Expr> rExpr);
                void accept(Visitor& visitor);

                const Token getOp() const { return op; }
                std::unique_ptr<Expr> getRightExpr() { return std::move(rExpr); };

            private:
                Token op;
                std::unique_ptr<Expr> rExpr; 
            };

        
    }
}