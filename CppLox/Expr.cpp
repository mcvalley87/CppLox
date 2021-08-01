
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

			boost::any BinaryExpr::accept(Visitor<boost::any>& visitor) const { return visitor.visitBinaryExpr(*this); }


			GroupingExpr::GroupingExpr(std::unique_ptr<Expr> expression) : expr(std::move(expression)) {
				assert(this->expr != nullptr);
			}

			boost::any GroupingExpr::accept(Visitor<boost::any>& visitor) const { return visitor.visitGroupingExpr(*this); }

			LiteralExpr::LiteralExpr(std::unique_ptr<Literal> lit) : literal(std::move(lit)) {

			}

			boost::any LiteralExpr::accept(Visitor<boost::any>& visitor) const { return visitor.visitLiteralExpr(*this); }

			UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> rExpr) :
				op(op),
				rExpr(std::move(rExpr)) {
				assert(this->rExpr != nullptr);
			}

			boost::any UnaryExpr::accept(Visitor<boost::any>& visitor) const { return visitor.visitUnaryExpr(*this); }

			// Variable Access Expressions

			VariableExpr::VariableExpr(Token name) : name(name) { }

			boost::any VariableExpr::accept(Visitor<boost::any>& visitor) const { return visitor.visitVariableExpr(*this); }

	}
}
