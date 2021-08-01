#include "Visitor.h"

namespace Lox {
	namespace Interpreter {

		/// <summary>
		/// Attempts to interpret the statement tree, going through all of the various expressions in proper order.
		/// </summary>
		/// <param name="statements">the list of statements to interpret</param>
		void InterpreterVisitor::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
			try {
				for (const auto& stmtptr : statements) {
					//assert(stmtptr != nullptr);
					if (stmtptr == nullptr) return;
					execute(*stmtptr);
				}
			}
			catch (RuntimeError rError) {
				std::cerr << rError.what() << std::endl;
			}
		}

		/// <summary>
		/// Executes the expressions contained in the statements, walking through with a visitor.
		/// </summary>
		/// <param name="stmt"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::execute(const Stmt& stmt) { return stmt.accept(*this); }


		/// <summary>
		/// If we have a print statement then we just need to evaluate the expression and then print its result
		/// </summary>
		/// <param name="stmt"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::visitPrintStmt(const PrintStmt& stmt) {

			auto value = evaluate(stmt.getExpr());
			std::cout << stringify(value) << std::endl;
			return nullptr;
		}

		/// <summary>
		/// If we have an actual expression statement without a print then we still need to process the expression and evaluate its contents
		/// but we don't display the result.
		/// </summary>
		/// <param name="stmt"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::visitExpressionStmt(const ExpressionStmt& stmt) {
			evaluate(stmt.getExpr());
			return nullptr;
		}

		boost::any InterpreterVisitor::visitVariableStmt(const VariableStmt& stmt) {

			auto value;

			if (stmt.getExpr() != nullptr) {
				value = evaluate(stmt.getExpr());
			}

			globalEnv.define(stmt.getName().getLexeme(), value);
			return nullptr;
		}

	}
}