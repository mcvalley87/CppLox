#include "Env.h"
#include "Error.h"


namespace Lox {
	namespace Interpreter {

		Env::Env(std::unique_ptr<Env> enclosing) : enclosing(std::move(enclosing)) {};

		void Env::define(std::string name, boost::any value) {
			std::cout << name << std::endl;
			std::cout << boost::any_cast<std::string>(value) << std::endl;

			values[name] = value;

			std::cout << "value: " << boost::any_cast<std::string>(values[name]) << std::endl;
		}

		void Env::assign(Token name, boost::any value) {
			if (values.count(name.getLexeme()) > 0) {
				values[boost::any_cast<std::string>(name.getLexeme())] = value;
				return;
			}

			if (enclosing != nullptr) {
				enclosing->assign(name, value);
				return;
			}

			std::string errorMessage = "Undefined variable '" + name.getLexeme() + "'.";
			throw new RuntimeError(name, errorMessage.c_str());
		}

		boost::any Env::get(Token name) {
			if (values.count(name.getLexeme())) {
				return values[name.getLexeme()];
			}

			if (enclosing != nullptr) return enclosing->get(name);

			std::string error = "Undefined variable '" + name.getLexeme() + "'.";
			throw RuntimeError(name, error.c_str());
		}
	}
}