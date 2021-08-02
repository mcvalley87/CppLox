#include "Visitor.h"

namespace Lox {

	namespace Interpreter {

		InterpreterVisitor::InterpreterVisitor() {

			gEnv = std::make_unique<Env>(nullptr);
		}
	}
}