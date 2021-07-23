#pragma once
#include <string>
#include<boost/any.hpp>
namespace Lox {

	namespace Interpreter {
		class Literal {
		public:
			Literal()=default;

			virtual std::string toString() const = 0;
		};

		class LoxBool : public Literal {
		public:
			LoxBool(bool val) : value(val) {};
			std::string toString() const override { return value ? "true" : "false"; }
		private:
			bool value;
		};

		class LoxDouble : public Literal {
		public:
			LoxDouble(double val) : value(val) {};
			std::string toString() const override { return std::to_string(value); }

		private:
			double value;
		};

		class LoxString : public Literal {
		public:
			LoxString(std::string val) : value(val) {};
			std::string toString() const override { return value; }

		private:
			std::string value;
		};

		class LoxNil : public Literal {
		public:
			LoxNil() = default;
			std::string toString() const override { return "nil"; }
		};
	};
};