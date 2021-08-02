#pragma once

#include <iostream>
#include<vector>
#include<memory>
#include<stdexcept>

#include "Tokens.h"

namespace Lox {
	namespace Interpreter {

		class Token;

		class Env {
		public:
			Env(std::unique_ptr<Env> enclosing);

			void define(std::string name, boost::any value);
			void assign(Token name, boost::any value);
			boost::any get(Token name); 
		private:
			std::unordered_map<std::string, boost::any> values;
			std::unique_ptr<Env> enclosing;
		};
	}
}