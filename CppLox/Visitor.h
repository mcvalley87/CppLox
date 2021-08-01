#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <boost/any.hpp>

#include "Expr.h"
#include "Error.h"
#include "Stmt.h"
#include "Env.h"

namespace Lox {
	namespace Interpreter {

		class Expr;
		class BinaryExpr;
		class GroupingExpr;
		class LiteralExpr;
		class UnaryExpr;
		class VariableExpr;
		class AssignExpr;
		class Stmt;
		class PrintStmt;
		class ExpressionStmt;
		class VariableStmt;
		class BlockStmt;

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
				virtual R visitVariableExpr(const VariableExpr& expr) = 0;
				virtual R visitAssignExpr(const AssignExpr& expr) = 0;
			};

			class ExprVisitor : public Visitor<boost::any> {
			public:

				~ExprVisitor() = default;

				virtual boost::any visitBinaryExpr(const BinaryExpr& expr) = 0;
				virtual boost::any visitGroupingExpr(const GroupingExpr& expr) = 0;
				virtual boost::any visitLiteralExpr(const LiteralExpr& expr) = 0;
				virtual boost::any visitUnaryExpr(const UnaryExpr& expr) = 0;
				virtual boost::any visitVariableExpr(const VariableExpr& expr) = 0;
				virtual boost::any visitAssignExpr(const AssignExpr& expr) = 0;
			};

			class AstPrinter : public ExprVisitor {
			public:
				AstPrinter() = default;
				~AstPrinter() = default;

				boost::any visitBinaryExpr(const BinaryExpr& expr) override;
				boost::any visitGroupingExpr(const GroupingExpr& expr) override;
				boost::any visitLiteralExpr(const LiteralExpr& expr) override;
				boost::any visitUnaryExpr(const UnaryExpr& expr) override;
				boost::any visitVariableExpr(const VariableExpr& expr) override;
				boost::any print(const Expr& expr);
			};
			///
			///
			/// 
			/// 
			template<typename R>
			class StmtVisitor {
			public:
				virtual ~StmtVisitor() = default;

			public:
				// set to zero to avoid linker problem encountered
				virtual R visitPrintStmt(const PrintStmt& stmt) = 0;
				virtual R visitExpressionStmt(const ExpressionStmt& stmt) = 0;
				virtual R visitVariableStmt(const VariableStmt& stmt) = 0;
				virtual R visitBlockStmt(const BlockStmt& stmt) = 0;
			};

			class PrimeStmtVisitor : public StmtVisitor<boost::any> {
			public:
				virtual ~PrimeStmtVisitor() = default;

			public:
				// set to zero to avoid linker problem encountered
				virtual boost::any visitPrintStmt(const PrintStmt& stmt) = 0;
				virtual boost::any visitExpressionStmt(const ExpressionStmt& stmt) = 0;
				virtual boost::any visitVariableStmt(const VariableStmt& stmt) = 0;
				virtual boost::any visitBlockStmt(const BlockStmt& stmt) = 0;
			};
			///
			///
			/// 
			/// 
			class InterpreterVisitor : public ExprVisitor, public PrimeStmtVisitor {
			public:

				~InterpreterVisitor() = default;

				void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);
			
			private:
				//Expression visitors
				boost::any visitBinaryExpr(const BinaryExpr& expr) override;
				boost::any visitGroupingExpr(const GroupingExpr& expr) override;
				boost::any visitLiteralExpr(const LiteralExpr& expr) override;
				boost::any visitUnaryExpr(const UnaryExpr& expr) override;
				boost::any visitVariableExpr(const VariableExpr& expr) override;
				boost::any visitAssignExpr(const AssignExpr& expr) override;

				//Statement visitors
				boost::any visitPrintStmt(const PrintStmt& stmt) override;
				boost::any visitExpressionStmt(const ExpressionStmt& stmt) override;
				boost::any visitVariableStmt(const VariableStmt& stmt) override;
				boost::any visitBlockStmt(const BlockStmt& stmt) override;
			private:

				//global environment by default
				Env gEnv;

				/// <summary>
				/// Runtime error handling
				/// </summary>
				RuntimeError error(Token token, const char* message) const;

				/// <summary>
				/// Helpers for expression eval
				/// </summary>
				
				boost::any evaluate(const Expr& expr);
				bool isTruthy(const boost::any obj);
				bool isEqual(const boost::any a, const boost::any b) const;
				void checkNumberOperand(Token op, const boost::any operand) const;
				void checkNumberOperands(Token op, const boost::any left, const boost::any right) const;
				void checkStringOperands(Token op, const boost::any left, const boost::any right) const;
				std::string stringify(boost::any object);

				/// <summary>
				/// Execute statements
				/// </summary>
				boost::any execute(const Stmt& stmt);
				boost::any executeBlock(const std::vector<std::unique_ptr<Stmt>>& stmts, const Env& lEnv);
			};


	}
}
