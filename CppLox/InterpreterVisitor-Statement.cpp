#include "Visitor.h"

namespace Lox {
	namespace Interpreter {

		boost::any InterpreterVisitor::visitPrintStmt(const PrintStmt& stmt) {
			return nullptr;
		}
		boost::any InterpreterVisitor::visitExpressionStmt(const ExpressionStmt& stmt) {
			return nullptr;
		}
	}
}