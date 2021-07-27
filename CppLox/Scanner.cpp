#include "Scanner.h"
#include "Interpreter.h"
#include <iostream>
#include <sstream>

namespace Lox {

	namespace Interpreter {

		/// <summary>
		/// Checks to see if the Scanner has reached the end of $source
		/// </summary>
		/// <returns></returns>
		bool Scanner::isAtEnd() {
			return current >= static_cast<int>(source.size());
		};
		
		/// <summary>
		/// Look at the current character in the $source string without consuming it
		/// </summary>
		/// <returns></returns>
		char Scanner::peek() {
			if (isAtEnd()) return '\0';
			return source.at(current);
		}
		/// <summary>
		/// Look ahead one character in the $source string without consuming any characters
		/// </summary>
		/// <returns></returns>
		char Scanner::peekNext() {
			if ((current + 1) >= static_cast<int>(source.size())) return '\0';
			return source.at(current + 1);
		}
		/// <summary>
		/// pull a token from our $source
		/// </summary>
		void Scanner::scanToken() {
			auto c = advance();

			switch (c) {
			case '(': addToken(TokenType::LEFT_PAREN); break;
			case ')': addToken(TokenType::RIGHT_PAREN); break;
			case '{': addToken(TokenType::LEFT_BRACE); break;
			case '}': addToken(TokenType::RIGHT_BRACE); break;
			case ',': addToken(TokenType::COMMA); break;
			case '.': addToken(TokenType::DOT); break;
			case '-': addToken(TokenType::MINUS); break;
			case '+':
				addToken(match('+') ? TokenType::PLUS_PLUS : TokenType::PLUS);
				break;
			case ';': addToken(TokenType::SEMICOLON); break;
			case '*': addToken(TokenType::STAR); break;
			case '!':
				addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
				break;
			case '=':
				addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
				break;
			case '<':
				addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
				break;
			case '>':
				addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
				break;
			case '/':
				if (match('/')) { // is it a comment?
					while (peek() != '\n' && !isAtEnd()) { advance(); };
				}
				else {
					addToken(TokenType::SLASH);
				};
				break;
			case ' ':
			case '\r':
			case '\t':
				//ignore whitespace
				break;
			case '\n':
				line++;
				break;
			case '"': string(); break;

			default:
				if (isDigit(c)) {
					number();
				}
				else {
					Lox::Interpreter::Interpreter::error(line, "Unexpected Character");
				}
				break;
			}
		};

		/// <summary>
		/// If we are dealing with a string literal, pull the entire string into a token.
		/// </summary>
		void Scanner::string() {
			while (peek() != '"' && !isAtEnd()) { // keep reading through till we hit that other quote symbol
				if (peek() == '\n') line++; // strings can go onto a newline, need to update line
				advance();
			}

			if (isAtEnd()) { // we have reached the end of the source string without finding the end
				Interpreter::error(line, "Unterminated string.");
			}
			else {

				// don't forget the closing "
				advance();
				std::string value = source.substr(start + 1, current - start - 2); // remove " from each end before adding string
				addToken(TokenType::STRING, value);
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="c"></param>
		/// <returns></returns>
		bool Scanner::isDigit(char c) {
			return c >= '0' && c <= '9';
		};

		void Scanner::number() {
			while (isDigit(peek())) advance(); //consume tokens as long as we find digits;

			if (peek() == '.' && isDigit(peekNext())) {
				//consume the "."
				advance();
			}

			while (isDigit(peek())) advance(); // consume the rest of the number

			std::string s = source.substr(start, current - start);
			std::istringstream ss(s);

			double d;

			ss >> d;

			addToken(TokenType::NUMBER, d);
		}
		/// <summary>
		/// Pull an additional character to compare with expected. if they are the same then
		/// we can eat through the character in $source, otherwise we stay at our current spot
		/// going forward with interpretation.
		/// </summary>
		/// <param name="expected"></param>
		/// <returns></returns>
		bool Scanner::match(char expected) {
			if (isAtEnd()) return false;
			if (source.at(current) != expected) return false;

			++current;
			return true;
		}; // check to see if there is a match-- conditional advance
		
		/// <summary>
		/// Advance forward into the $source string
		/// </summary>
		/// <returns>the next character in the $source string</returns>
		char Scanner::advance() {
			return source.at(current++);
		};
		/// <summary>
		/// Add a token to our list
		/// </summary>
		/// <param name="type"> passes the type of token we are adding</param>
		void Scanner::addToken(TokenType type) {
			addToken(type, NULL);
		};
		/// <summary>
		/// Add a token to our list
		/// </summary>
		/// <param name="type">passes the type of token we are adding</param>
		/// <param name="literal"> the literal value of the token</param>
		void Scanner::addToken(TokenType type, boost::any literal) {
			std::string text = source.substr(start, current - start);
			tokens.push_back(Token(type, text, literal, line));
		}; 
		/// <summary>
		/// scan through the entirety of $source to find tokens
		/// </summary>
		/// <returns></returns>
		std::vector<Token> Scanner::scanTokens() {
			while (!isAtEnd()) {
				start = current;
				scanToken();
			}

			tokens.push_back(Token(TokenType::FILE_END, "",NULL,line));
			return tokens;
		};
	}

}