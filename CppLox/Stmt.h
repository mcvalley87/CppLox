#pragma once
#include "Expr.h"

namespace Lox {
	namespace Interpreter {

		template<typename R> class StmtVisitor;
		class Expr;

		class Stmt {
		public:
			virtual ~Stmt() = default;

			virtual boost::any accept(StmtVisitor<boost::any>& visitor) const = 0;
		};

		class PrintStmt : public Stmt {
		public:
			PrintStmt(std::unique_ptr<Expr> expr);
			boost::any accept(StmtVisitor<boost::any>& visitor) const override;

			const Expr& getExpr() const { return *expr; }

		private:
			std::unique_ptr<Expr> expr;
		};

		class ExpressionStmt : public Stmt {
		public:
			ExpressionStmt(std::unique_ptr<Expr> expr);
			boost::any accept(StmtVisitor<boost::any>& visitor) const override;

			const Expr& getExpr() const { return *expr; }

		private:
			std::unique_ptr<Expr> expr;
		};
	}
}