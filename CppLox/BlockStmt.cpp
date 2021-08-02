#include "Stmt.h"

namespace Lox {
	namespace Interpreter {

		BlockStmt::BlockStmt(std::vector<std::unique_ptr<Stmt>> stmts) : stmts(std::move(stmts)) { };

		boost::any BlockStmt::accept(StmtVisitor<boost::any>& visitor) const {
			return visitor.visitBlockStmt(*this);
		}
	}
}