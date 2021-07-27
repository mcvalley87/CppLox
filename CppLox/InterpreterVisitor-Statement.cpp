#include "Visitor.h"

namespace Lox {
	namespace Interpreter {

		void InterpreterVisitor::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
			try {
				for (const auto& stmtptr : statements) {
					assert(stmtptr != nullptr);
					execute(*stmtptr);
				}
			}
			catch (RuntimeError rError) {
				std::cerr << rError.what() << std::endl;
			}
		}

		boost::any InterpreterVisitor::execute(const Stmt& stmt) { return stmt.accept(*this); }

		boost::any InterpreterVisitor::visitPrintStmt(const PrintStmt& stmt) {

			auto value = evaluate(stmt.getExpr());
			std::cout << stringify(value) << std::endl;
			return nullptr;
		}
		boost::any InterpreterVisitor::visitExpressionStmt(const ExpressionStmt& stmt) {
			evaluate(stmt.getExpr());
			return nullptr;
		}

	}
}