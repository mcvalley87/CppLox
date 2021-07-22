#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace Lox {

	namespace Interpreter {

		class Interpreter {

		public:
			static bool hadError;
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
			static void report(int line, std::string where, std::string message) {
				std::cerr << "[line" << line << "] Error" << where << ": " << message;
				hadError = true;
			};
		};
	}
}
