#include "Visitor.h"


namespace Lox {
	namespace Interpreter {

		/// <summary>
		/// Attempts to interpret the statement tree, going through all of the various expressions in proper order.
		/// </summary>
		/// <param name="statements">the list of statements to interpret</param>
		void InterpreterVisitor::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
			try {
				for (const auto& stmtptr : statements) {
					assert(stmtptr != nullptr);
					if (stmtptr == nullptr) return;
					execute(*stmtptr);
				}
			}
			catch (RuntimeError rError) {
				std::cerr << rError.what() << std::endl;
			}
		}

		/// <summary>
		/// Executes the expressions contained in the statements, walking through with a visitor.
		/// </summary>
		/// <param name="stmt"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::execute(const Stmt& stmt) { return stmt.accept(*this); }

		/// <summary>
		/// Executes a block of statements
		/// </summary>
		/// <param name="stmts"></param>
		/// <param name="lEnv"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::executeBlock(const std::vector<std::unique_ptr<Stmt>>& stmts, std::unique_ptr<Env> lEnv) {

			EnterEnviromentGuard ee{ *this, std::move(lEnv) };

			for (const auto& stmtPtr : stmts) {
				assert(stmtPtr != nullptr);
				execute(*stmtPtr);
			}
			return nullptr;
		}
		/// <summary>
		/// If we have a print statement then we just need to evaluate the expression and then print its result
		/// </summary>
		/// <param name="stmt"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::visitPrintStmt(const PrintStmt& stmt) {

			auto value = evaluate(stmt.getExpr());
			std::cout << stringify(value) << std::endl;
			return nullptr;
		}

		/// <summary>
		/// If we have an actual expression statement without a print then we still need to process the expression and evaluate its contents
		/// but we don't display the result.
		/// </summary>
		/// <param name="stmt"></param>
		/// <returns></returns>
		boost::any InterpreterVisitor::visitExpressionStmt(const ExpressionStmt& stmt) {
			evaluate(stmt.getExpr());
			return nullptr;
		}

		boost::any InterpreterVisitor::visitVariableStmt(const VariableStmt& stmt) {

			boost::any value;

			if (stmt.hasInit()) {
				value = evaluate(stmt.getExpr());
			}

			//std::cout << "variablevisited" << std::endl;
			assert(gEnv != nullptr);

			gEnv->define(stmt.getName().getLexeme(), value);
			return nullptr;
		}

		boost::any InterpreterVisitor::visitBlockStmt(const BlockStmt& stmt) {
			//auto blockEnv = std::make_unique<Env>(gEnv.get());
			executeBlock(stmt.getStatements(),std::move(gEnv));

			return nullptr;
		}

		///
		///
		/// 
		InterpreterVisitor::EnterEnviromentGuard::EnterEnviromentGuard(InterpreterVisitor& i, std::unique_ptr<Env> env)
			: i(i)
		{
			previous = std::move(i.gEnv);
			i.gEnv = std::move(env);
		}

		InterpreterVisitor::EnterEnviromentGuard::~EnterEnviromentGuard()
		{
			i.gEnv = std::move(previous);
		}
	}
}