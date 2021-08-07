#include "Tokens.h"
#include "Scanner.h"
#include "Interpreter.h"
#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
namespace Lox {


	namespace Interpreter {

		bool Interpreter::hadError = false;
		bool Interpreter::hadRuntimeError = false;

		/// <summary>
		/// Run through the file specified by $path and convert it into a string and then scan that string for tokens.
		/// </summary>
		/// <param name="path">The name of the Lox source file</param>
		void Interpreter::runFile(std::string path) {
			std::ifstream file(path);
			std::string str;

			if (file) { // if we were able to open the file
				std::ostringstream ss;
				ss << file.rdbuf(); // read data from file into a string stream
				str = ss.str(); // convert string stream to string
			}

			run(str);
			// Indicate an error if there was a problem running
			// the source provided
			if (Interpreter::hadError) std::exit(65);

			if (hadRuntimeError) std::exit(70);
		}

		void Interpreter::runPrompt() {

			for (;;) {
				std::string line;

				std::getline(std::cin, line);

				if (line.empty()) { // 
					break;
				}
				else {
					run(line);
					hadError = false;
					//hadRuntimeError = false;
				}
			}
			
		}
		/// <summary>
		/// Helper function for runFile and runPrompt. Scans through tokens.
		/// TO-DO == Implement
		/// </summary>
		/// <param name="source">The string we are going to parse for tokens</param>
		void Interpreter::run(std::string source) { // helper function
			Scanner scanner =  Scanner(source);
			std::vector<Token> tokens = scanner.scanTokens();

			//std::cout << "Result of Scanning..." << std::endl;
			//for (auto t : tokens) { std::cout << t.toString() << std::endl; }

			//std::cout << "--------------" << std::endl;

			Parser parser{ tokens };
			
			
			//std::unique_ptr<Expr> expression = parser.parse();

			auto statements = parser.parse();

			if (hadError) return; // stop if syntax error

			InterpreterVisitor interpreter;
			interpreter.interpret(statements);;
			
			if (hadRuntimeError) return;
		}
	}
}