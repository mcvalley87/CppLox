#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <boost/any.hpp>

#include "Expr.h"

namespace Lox {
	namespace Interpreter {

		class Expr;
		class BinaryExpr;
		class GroupingExpr;
		class LiteralExpr;
		class UnaryExpr;

			class Visitor {
			public:
				virtual ~Visitor() = default;

			public:
				// set to zero to avoid linker problem encountered
				virtual void visitBinaryExpr(BinaryExpr& expr) = 0;
				virtual void visitGroupingExpr(GroupingExpr& expr) = 0;
				virtual void visitLiteralExpr(LiteralExpr& expr) = 0;
				virtual void visitUnaryExpr(UnaryExpr& expr) = 0;
			};

			class AstPrinter : public Visitor {
			public:

				~AstPrinter() = default;

				void print(Expr& expr);

				void visitBinaryExpr(BinaryExpr& expr) override;
				void visitGroupingExpr(GroupingExpr& expr) override;
				void visitLiteralExpr(LiteralExpr& expr) override;
				void visitUnaryExpr(UnaryExpr& expr) override;

				void parenthesize(std::string name, std::vector<std::unique_ptr<Expr>> vExprs);
			};

			

	}
}
