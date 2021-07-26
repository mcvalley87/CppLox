#pragma once
#include <iostream>
#include<vector>
#include<memory>
#include<stdexcept>
#include "Tokens.h"

namespace Lox {

	namespace Interpreter {

		class RuntimeError : public std::runtime_error {
			public:
				RuntimeError(Token token, const char *message) : std::runtime_error(message), token(token) {};

		private:
			Token token;
		};
	}
}