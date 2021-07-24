#include "Visitor.h"

/// <summary>
/// Todo: need to fix casting issues in the AstPrinter class
/// </summary>
namespace Lox {
	namespace Interpreter {

		
			boost::any AstPrinter::print(const Expr& expr) {
				return boost::any_cast<std::string>(expr.accept(*this));
			}

			boost::any AstPrinter::visitBinaryExpr(const BinaryExpr& expr) {
				
				std::string output;

				output.append("(");
				output.append(expr.getOp().getLexeme());
				output.append(" ");
				output.append(boost::any_cast<std::string>(expr.getLeftExpr().accept(*this)));
				output.append(boost::any_cast<std::string>(expr.getRightExpr().accept(*this)));
				output.append(")");

				return output;
			}

			boost::any AstPrinter::visitGroupingExpr(const GroupingExpr& expr) {
				std::string output;

				output.append("(");
				output.append("group ");
				output.append(boost::any_cast<std::string>(expr.getExpr().accept(*this)));
				output.append(")");

				return output;
			}

			boost::any AstPrinter::visitLiteralExpr(const LiteralExpr& expr) {

				std::string output;

				if (expr.getLiteral().toString() == "") output.append("Nil");

				output.append(expr.getLiteral().toString());
				
				return output;
			}

			boost::any AstPrinter::visitUnaryExpr(const UnaryExpr& expr) {
				std::string output;

				output.append("(");
				output.append(expr.getOp().getLexeme());
				output.append(" ");
				output.append(boost::any_cast<std::string>(expr.getRightExpr().accept(*this)));
				output.append(")");

				return output;
			}

			

	}
}