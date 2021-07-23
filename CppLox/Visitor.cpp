#include "Visitor.h"

/// <summary>
/// Todo: need to fix casting issues in the AstPrinter class
/// </summary>
namespace Lox {
	namespace Interpreter {

			boost::any AstPrinter::print(Expr& expr) {
				return expr.accept(*this);
			}

			boost::any AstPrinter::visitBinaryExpr(BinaryExpr& expr) {

				/*std::vector<std::unique_ptr<Expr>> vExprs;

				vExprs.push_back(std::move(expr.getLeftExpr()));
				vExprs.push_back(std::move(expr.getRightExpr()));
				parenthesize(expr.getOp().getLexeme(), std::move(vExprs));*/

				return nullptr;
			}

			boost::any AstPrinter::visitGroupingExpr(GroupingExpr& expr) {
				/*std::vector<std::unique_ptr<Expr>> vExp;

				vExp.push_back(std::move(expr.getExpr()));
				parenthesize("group", std::move(vExp));*/

				return nullptr;
			}

			boost::any AstPrinter::visitLiteralExpr(LiteralExpr& expr) {

				/*if (expr.getLiteral() == nullptr) std::cout << "Nil";

				std::cout << expr.getLiteral()->toString();*/
				
				return nullptr;
			}

			boost::any AstPrinter::visitUnaryExpr(UnaryExpr& expr) {
				/*std::vector<std::unique_ptr<Expr>> vExp;
				vExp.push_back(std::move(expr.getRightExpr()));
				parenthesize(expr.getOp().getLexeme(), std::move(vExp));
				*/

				return nullptr;
			}

			boost::any AstPrinter::parenthesize(std::string name, std::vector<std::unique_ptr<Expr>> vExprs) {

				/*std::cout << "(" << name;
				for (auto&& expr : vExprs) {
					std::cout << " ";
					expr->accept(*this);
				}

				std::cout << ")";*/

				return nullptr;
			}

	}
}