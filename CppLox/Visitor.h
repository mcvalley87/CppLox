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
				virtual void visitBinaryExpr(BinaryExpr& expr);
				virtual void visitGroupingExpr(GroupingExpr& expr);
				virtual void visitLiteralExpr(LiteralExpr& expr);
				virtual void visitUnaryExpr(UnaryExpr& expr);
			};

			class AstPrinter : public Visitor {
			public:

				~AstPrinter() = default;

				void print(Expr& expr);

				void visitBinaryExpr(BinaryExpr& expr);
				void visitGroupingExpr(GroupingExpr& expr);
				void visitLiteralExpr(LiteralExpr& expr);
				void visitUnaryExpr(UnaryExpr& expr);

				void parenthesize(std::string name, std::vector<std::unique_ptr<Expr>> vExprs);
			};

			

	}
}
