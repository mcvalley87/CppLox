#pragma once
#include <iostream>
#include<vector>
#include<memory>
#include<stdexcept>
#include "Tokens.h"
#include "Expr.h"
#include "Stmt.h"
#include "Visitor.h"
#include "Error.h"

namespace Lox {
	namespace Interpreter {

		class Parser {
		private:
			std::vector<Token> tokens;
			int current{ 0 };

		public:
			Parser(std::vector<Token> tokens);
			std::unique_ptr<Expr> parse();
		private:

			class ParseError : public std::runtime_error {
			public:
				ParseError() : std::runtime_error("") {};
			};

			/* need to be able to throw errors*/
			ParseError error(Token token, const char* message) const;

			/* Lowest precedence -- Expression*/
			std::unique_ptr<Expr> expression();
			/* Binary ops*/
			std::unique_ptr<Expr> equality(); // BANG_EQUAL or EQUAL_EQUAL
			std::unique_ptr<Expr> comparison(); // GREATER, GREATER_EQUAL, LESS,  LESS_EQUAL
			std::unique_ptr<Expr> term(); // PLUS and MINUS
			std::unique_ptr<Expr> factor(); // STAR and SLASH
			/*Unary operators*/
			std::unique_ptr<Expr> unary(); // BANG or MINUS
			/*Highest precedence-- primaries*/
			std::unique_ptr<Expr> primary();
			

			/*Helpers*/
			template<typename ...Args>
			bool match(Args...args); // match to particular set of tokens
			bool check(TokenType type) const; // is current token of given type? only peeks, doesn't consume
			Token advance(); //consumes the current token, returning it similar to method in Scanner
			Token consume(TokenType type, const char* message);
			bool isAtEnd() const; // are we at the end of the file?
			Token peek() const; // look at the current token without consuming
			Token previous() const;// look at prior token
			void synchronize(); // synchronize to clear out call frames
		};
	}
}