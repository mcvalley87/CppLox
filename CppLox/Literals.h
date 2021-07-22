#pragma once
#include <string>
#include<boost/any.hpp>
namespace Lox {

	namespace Interpreter {
		class LiteralObject {
		public:
			LiteralObject()=default;

			std::string toString();
		};
	};
};