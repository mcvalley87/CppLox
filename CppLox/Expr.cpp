
#include <cassert>
#include "Expr.h"

namespace Lox {
	namespace Interpreter {


			//// Binary Operators

			/// <summary>
			/// 
			/// </summary>
			/// <param name="left"></param>
			/// <param name="operator,Expr right"></param>
			BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) :
				lExpr(std::move(left)),
				op(op),
				rExpr(std::move(right)) {

				assert(this->lExpr != nullptr);
				assert(this->rExpr != nullptr);

			}

			void BinaryExpr::accept(Visitor& visitor) { visitor.visitBinaryExpr(*this); }


			GroupingExpr::GroupingExpr(std::unique_ptr<Expr> expression) : expr(std::move(expression)) {
				assert(this->expr != nullptr);
			}

			void GroupingExpr::accept(Visitor& visitor) { visitor.visitGroupingExpr(*this); }

			LiteralExpr::LiteralExpr(std::unique_ptr<Literal> lit) : literal(std::move(lit)) {

			}

			void LiteralExpr::accept(Visitor& visitor) { visitor.visitLiteralExpr(*this); }

			UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> rExpr) :
				op(op),
				rExpr(std::move(rExpr)) {
				assert(this->rExpr != nullptr);
			}

			void UnaryExpr::accept(Visitor& visitor) { return visitor.visitUnaryExpr(*this); }

	}
}
