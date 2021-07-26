#include "Visitor.h"

namespace Lox {
	namespace Interpreter {
		boost::any InterpreterVisitor::visitBinaryExpr(const BinaryExpr& expr) {
			auto left = evaluate(expr.getLeftExpr());
			auto right = evaluate(expr.getRightExpr());
			TokenType optype = expr.getOp().getType();

			switch (optype) {
			case TokenType::GREATER:
				return boost::any_cast<double>(left) > boost::any_cast<double>(right);
			case TokenType::GREATER_EQUAL:
				return boost::any_cast<double>(left) >= boost::any_cast<double>(right);
			case TokenType::LESS:
				return boost::any_cast<double>(left) < boost::any_cast<double>(right);
			case TokenType::LESS_EQUAL:
				return boost::any_cast<double>(left) <= boost::any_cast<double>(right);
			case TokenType::BANG_EQUAL:
				return !isEqual(left,right);
			case TokenType::EQUAL_EQUAL:
				return isEqual(left,right);
			case TokenType::MINUS:
				return boost::any_cast<double>(left) - boost::any_cast<double>(right);
			case TokenType::PLUS:
				return boost::any_cast<double>(left) + boost::any_cast<double>(right);
			case TokenType::PLUS_PLUS:
				return boost::any_cast<std::string>(left) + boost::any_cast<std::string>(right);
			case TokenType::SLASH:
				return boost::any_cast<double>(left) / boost::any_cast<double>(right);
			case TokenType::STAR:
				return boost::any_cast<double>(left) / boost::any_cast<double>(right);
			}
			
			return nullptr;
		}

		boost::any InterpreterVisitor::visitGroupingExpr(const GroupingExpr& expr) { return evaluate(expr.getExpr()); }

		boost::any InterpreterVisitor::visitLiteralExpr(const LiteralExpr& expr) { return expr.getLiteral().getValue(); }

		boost::any InterpreterVisitor::visitUnaryExpr(const UnaryExpr& expr) {
			boost::any right = evaluate(expr.getRightExpr());

			switch (expr.getOp().getType()) {

			case TokenType::BANG:
				return !isTruthy(right);
			case TokenType::MINUS:
				return -boost::any_cast<double>(right);
			}

			return nullptr;
		}

		boost::any InterpreterVisitor::evaluate(const Expr& expr) { return expr.accept(*this); }

		bool InterpreterVisitor::isTruthy(boost::any obj) {
			try {
				return boost::any_cast<bool>(obj);
			}
			catch (boost::bad_any_cast error) {
				return false;
			}
		};

		bool InterpreterVisitor::isEqual(const boost::any a, const boost::any b) const {

			if (a.type() != b.type()) {
				return false;
			}
			else
			{
				if (a.type() == typeid(double)) {
					return boost::any_cast<double>(a) == boost::any_cast<double>(b);
				}
				else if (a.type() == typeid(std::string))
				{
					return boost::any_cast<std::string>(a).compare(boost::any_cast<std::string>(b));
				}
			}

			return false;
		}
	}
}