#include "Tokens.h"
#include "Scanner.h"
#include "Interpreter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
namespace Lox {


	namespace Interpreter {

		bool Interpreter::hadError = false;

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
			if (Interpreter::hadError) {

			};
		}

		void Interpreter::runPrompt() {

			for (;;) {
				std::string line;

				std::cin >> line;

				if (line.empty()) { // 
					break;
				}
				else {
					run(line);
					hadError = false;
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

			// For now, just print the tokens.
			for (Token token : tokens) {
				std::cout << token.toString() << "\n";
			}

		}
	}
}