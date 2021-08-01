#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Error.h"
#include "Expr.h"
#include "Visitor.h"
#include "Env.h"

namespace Lox {

	namespace Interpreter {

		class Interpreter {

		public:
			static bool hadError;
			static bool hadRuntimeError;
			Interpreter() = default;
			
		
		public:
			void runFile(std::string path);
			void runPrompt();
			static void run(std::string source);

		/// <summary>
		/// Error handling
		/// </summary>
		public:
			
			/// <summary>
			/// report any errors that occur during operation of the interpreter
			/// </summary>
			/// <param name="line"></param>
			/// <param name="message"></param>
			static void error(int line, std::string message) {
				report(line, "", message);
			}

			static void error(Token token, std::string message) {
				if (token.getType() == TokenType::FILE_END) {
					report(token.getLine(), " at end", message);
				}
				else {
					report(token.getLine(), token.getLexeme(), message);
				}
				hadError = false;
			}

			static void report(int line, std::string where, std::string message) {
				std::cerr << "[line" << line << "] Error" << where << ": " << message << std::endl;
				hadError = true;
			};

			static void runtimeError(RuntimeError error) {
				std::cerr << error.what() << std::endl;
				hadRuntimeError = true;
			}

		};
	}
}
