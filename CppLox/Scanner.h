#pragma once
#include <unordered_map>
#include <map>
#include <iostream>
#include <boost/any.hpp>
#include "Tokens.h"
#include "Literals.h"

namespace Lox {

	namespace Interpreter {

		/// <summary>
		/// Scanner class-- this class holds the methods and members necessary to read through a particular input string
		/// and to tokenize said input string for future input into parsers stage of interpretation
		/// </summary>
		class Scanner {
			std::string source;
			std::vector<Token> tokens;
			//members used to keep track of location in string
			int start = 0;
			int current = 0;
			int line = 1;

		private:
			bool isAtEnd(); // are we at the end of the source?
			void scanToken(); // pull a token from our source
			bool match(char expected); // check to see if there is a match-- conditional advance
			char peek(); // peek into the $source string at the current location without consuming the character
			char peekNext(); //look athead an additional character in the $source string without consuming characters
			char advance(); // advance forward in source
			void addToken(TokenType type); // add a token to our list
			void addToken(TokenType type, boost::any literal); // add a token
			void string(); // take in string literal token
			bool isDigit(char c); // is the character we are looking at a digit
			void number(); // consume number literal
		public:
			Scanner(std::string s) : source(s), start(0), current(0), line(0) {
				//std::cout << "The Source being read looks like\n\n" << source << " and is of length" << static_cast<int>(source.size()) << std::endl;
			};
			Scanner() = default;

			std::vector<Token> scanTokens();// scan through source to find tokens

		};
	}
};