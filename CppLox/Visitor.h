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

			template<typename R>
			class Visitor {
			public:
				virtual ~Visitor() = default;

			public:
				// set to zero to avoid linker problem encountered
				virtual R visitBinaryExpr(const BinaryExpr& expr) = 0;
				virtual R visitGroupingExpr(const GroupingExpr& expr) = 0;
				virtual R visitLiteralExpr(const LiteralExpr& expr) = 0;
				virtual R visitUnaryExpr(const UnaryExpr& expr) = 0;
			};

			class ExprVisitor : public Visitor<boost::any> {
			public:

				~ExprVisitor() = default;

				virtual boost::any visitBinaryExpr(BinaryExpr& expr) = 0;
				virtual boost::any visitGroupingExpr(GroupingExpr& expr) = 0;
				virtual boost::any visitLiteralExpr(LiteralExpr& expr) = 0;
				virtual boost::any visitUnaryExpr(UnaryExpr& expr) = 0;
			};

			class AstPrinter : public ExprVisitor {
			public:
				~AstPrinter() = default;

				boost::any visitBinaryExpr(BinaryExpr& expr) override;
				boost::any visitGroupingExpr(GroupingExpr& expr) override;
				boost::any visitLiteralExpr(LiteralExpr& expr) override;
				boost::any visitUnaryExpr(UnaryExpr& expr) override;

				boost::any parenthesize(std::string name, std::vector<std::unique_ptr<Expr>> vExprs);
				boost::any print(Expr& expr);
			};



			

	}
}
