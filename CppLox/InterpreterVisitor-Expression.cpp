#include "Visitor.h"

namespace Lox {
	namespace Interpreter {

		RuntimeError InterpreterVisitor::error(Token token, const char* message) const {
			return RuntimeError(token, message);
		}

		/*void InterpreterVisitor::interpret(const Expr& expression) {
			try {
				boost::any value = evaluate(expression);
				std::cout << stringify(value) << std::endl;
			}
			catch (RuntimeError rError) {
				std::cerr << rError.what() << std::endl;
			}
		}*/

		std::string InterpreterVisitor::stringify(boost::any object) {
			if (object.empty()) return "nil";

			if (object.type() == typeid (double)) {
				std::string text = std::to_string(boost::any_cast<double>(object));
				text = text.substr(0, text.length() - 6);

				return text;
			}

			return boost::any_cast<std::string>(object);
		}

		boost::any InterpreterVisitor::visitBinaryExpr(const BinaryExpr& expr) {
			auto left = evaluate(expr.getLeftExpr());
			auto right = evaluate(expr.getRightExpr());
			TokenType optype = expr.getOp().getType();

			//std::cout << "Value of left string operand is \"" << boost::any_cast<std::string>(left) << "\"\n";
			//std::cout << "Value of right string operand is \"" << boost::any_cast<std::string>(right) << "\"\n";

			switch (optype) {
			case TokenType::GREATER:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) > boost::any_cast<double>(right);
			case TokenType::GREATER_EQUAL:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) >= boost::any_cast<double>(right);
			case TokenType::LESS:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) < boost::any_cast<double>(right);
			case TokenType::LESS_EQUAL:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) <= boost::any_cast<double>(right);
			case TokenType::BANG_EQUAL:
				return !isEqual(left,right);
			case TokenType::EQUAL_EQUAL:
				return isEqual(left,right);
			case TokenType::MINUS:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) - boost::any_cast<double>(right);
			case TokenType::PLUS:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) + boost::any_cast<double>(right);
			case TokenType::PLUS_PLUS:
				checkStringOperands(expr.getOp(), left, right);
				return boost::any_cast<std::string>(left) + boost::any_cast<std::string>(right);
			case TokenType::SLASH:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) / boost::any_cast<double>(right);
			case TokenType::STAR:
				checkNumberOperands(expr.getOp(), left, right);
				return boost::any_cast<double>(left) * boost::any_cast<double>(right);
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

		boost::any InterpreterVisitor::visitVariableExpr(const VariableExpr& expr) {

			return globalEnv.get(expr.getVar());
		}
		boost::any InterpreterVisitor::evaluate(const Expr& expr) { return expr.accept(*this); }


		/* HELPER FUNCTIONS
				Functions here are for the purpose of helping out the interpreter.

		*/

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

		void InterpreterVisitor::checkNumberOperand(Token op, const boost::any operand) const {
			if (operand.type() == typeid(double)) return;
			throw error(boost::any_cast<Token>(op), "Operand must be a number.");
		}

		void InterpreterVisitor::checkNumberOperands(Token op, const boost::any left, const boost::any right) const {
			if (left.type() == typeid(double) && right.type() == typeid(double)) return;

			throw error(op, "Operands must be numbers.");
		}

		void InterpreterVisitor::checkStringOperands(Token op, const boost::any left, const boost::any right) const {
			if (left.type() == typeid(std::string) && right.type() == typeid(std::string)) return;

			throw error(op, "Operands must be strings");
		}
	}
}