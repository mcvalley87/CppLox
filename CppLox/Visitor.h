#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <boost/any.hpp>

#include "Expr.h"
#include "Error.h"

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

				virtual boost::any visitBinaryExpr(const BinaryExpr& expr) = 0;
				virtual boost::any visitGroupingExpr(const GroupingExpr& expr) = 0;
				virtual boost::any visitLiteralExpr(const LiteralExpr& expr) = 0;
				virtual boost::any visitUnaryExpr(const UnaryExpr& expr) = 0;
			};

			class AstPrinter : public ExprVisitor {
			public:
				AstPrinter() = default;
				~AstPrinter() = default;

				boost::any visitBinaryExpr(const BinaryExpr& expr) override;
				boost::any visitGroupingExpr(const GroupingExpr& expr) override;
				boost::any visitLiteralExpr(const LiteralExpr& expr) override;
				boost::any visitUnaryExpr(const UnaryExpr& expr) override;
				boost::any print(const Expr& expr);
			};

			class InterpreterVisitor : public ExprVisitor {
			public:

				~InterpreterVisitor() = default;

				void interpret(const Expr& expression);
				boost::any visitBinaryExpr(const BinaryExpr& expr) override;
				boost::any visitGroupingExpr(const GroupingExpr& expr) override;
				boost::any visitLiteralExpr(const LiteralExpr& expr) override;
				boost::any visitUnaryExpr(const UnaryExpr& expr) override;

			private:

				RuntimeError error(Token token, const char* message) const;

				boost::any evaluate(const Expr& expr);
				bool isTruthy(const boost::any obj);
				bool isEqual(const boost::any a, const boost::any b) const;
				void checkNumberOperand(Token op, const boost::any operand) const;
				void checkNumberOperands(Token op, const boost::any left, const boost::any right) const;
				void checkStringOperands(Token op, const boost::any left, const boost::any right) const;
				std::string stringify(boost::any object);
			};


			

	}
}
