#include "Visitor.h"

/// <summary>
/// Todo: need to fix casting issues in the AstPrinter class
/// </summary>
namespace Lox {
	namespace Interpreter {

			void AstPrinter::print(Expr& expr) {
				expr.accept(*this);
			}

			void AstPrinter::visitBinaryExpr(BinaryExpr& expr) {

				std::vector<std::unique_ptr<Expr>> vExprs;

				vExprs.push_back(std::move(expr.getLeftExpr()));
				vExprs.push_back(std::move(expr.getRightExpr()));
				parenthesize(expr.getOp().getLexeme(), std::move(vExprs));
			}

			void AstPrinter::visitGroupingExpr(GroupingExpr& expr) {
				std::vector<std::shared_ptr<Expr>> vExp;

				//vExp.push_back(expr.getExpr());
				//parenthesize("group", vExp);
			}

			void AstPrinter::visitLiteralExpr(LiteralExpr& expr) {
				if (expr.getLiteral() == nullptr) std::cout << "Nil";

				std::cout << expr.getLiteral();
			}

			void AstPrinter::visitUnaryExpr(UnaryExpr& expr) {


				//vExp.push_back(expr.getRightExpr());
				//return parenthesize(expr.getOp().getLexeme(), vExp);
			}

			void AstPrinter::parenthesize(std::string name, std::vector<std::unique_ptr<Expr>> vExprs) {

				std::cout << "(" << name;
			
			}

	}
}