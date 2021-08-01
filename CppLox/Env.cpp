#include "Env.h"

namespace Lox {
	namespace Interpreter {

		Env::Env() {}

		void Env::define(std::string name, boost::any& value); {
			values[name] = value;
		}

		boost::any Env::get(Token name); {
			if (values.find(name.getLexeme())) {
				return values[name.getLexeme()];
			}

			std::string error = "Undefined variable '" + name.getLexeme() + "'.";
			throw RuntimeError(name, error);
		}
	}
}