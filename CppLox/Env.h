#pragma once

#include "Tokens.h"

namespace Lox {
	namespace Interpreter {

		class Env {
		public:
			Env() = default;

			void define(std::string name, boost::any& value); 
			boost::any get(Token name); 
		private:
			std::unordered_map<std::string, boost::any&> values;
		};
	}
}