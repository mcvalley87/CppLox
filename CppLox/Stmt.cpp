#include "Stmt.h"

namespace Lox {

	namespace Interpreter {

		PrintStmt::PrintStmt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {
			assert(this->expr != nullptr);
		}

		boost::any PrintStmt::accept(StmtVisitor<boost::any>& visitor) const {
			return visitor.visitPrintStmt(*this);
		}

		ExpressionStmt::ExpressionStmt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {
			assert(this->expr != nullptr);
		}

		boost::any ExpressionStmt::accept(StmtVisitor<boost::any>& visitor) const {
			return visitor.visitExpressionStmt(*this);
		}
	}
}