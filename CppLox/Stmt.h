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

		class VariableStmt : public Stmt {
		public:
			VariableStmt(Token name, std::unique_ptr<Expr> init);
			boost::any accept(StmtVisitor<boost::any>& visitor) const override;

			const Expr& getExpr() const { return *init; }
			const Token& getName() const { return name; }
			bool hasInit() const { return init != nullptr; }
		private:
			std::unique_ptr<Expr> init;
			Token name;
		};

		class BlockStmt : public Stmt {
		public:
			BlockStmt(std::vector<std::unique_ptr<Stmt>> stmts);
			boost::any accept(StmtVisitor<boost::any>& visitor) const override;
			const std::vector<std::unique_ptr<Stmt>>& getStatements() const { return stmts; }
		private:
			std::vector<std::unique_ptr<Stmt>> stmts;
		};
	}
}