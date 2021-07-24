#include "Parser.h"

namespace Lox {
	namespace Interpreter {

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<Expr> Parser::expression() { return equality(); }

		std::unique_ptr<Expr> Parser::equality() {
			auto expr = comparison(); // equality is comparison ( ( "!=" | "==" ) comparison )*;

			while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) { // while we still have comparisons
				auto op = previous();
				auto right = comparison();
				// make a binary expression out of the previous result with the current comparison
				expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
			}
			return expr;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<Expr> Parser::comparison() {
			// comparison is addition ( ( GREATER | GREATER_EQUAL | LESS | LESS_EQUAL) addition)*
			auto expr = term();

			while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
				auto op = previous();
				auto right = term();
				expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
			}

			return expr;
		}

		std::unique_ptr<Expr> Parser::term() {
			auto expr = factor();

			while (match(TokenType::MINUS, TokenType::PLUS)) {
				auto op = previous();
				auto right = factor();

				expr = std::make_unique<BinaryExpr>(std::move(expr), op,std::move(right));
			}

			return expr;
		}

		std::unique_ptr<Expr> Parser::factor() {
			auto expr = unary();

			while (match(TokenType::SLASH, TokenType::STAR)) {
				auto op = previous();
				auto right = unary();

				expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
			}
			return expr;
		}

		std::unique_ptr<Expr> Parser::unary() {
			if (match(TokenType::BANG, TokenType::MINUS)) {
				auto op = previous();
				auto right = unary();
				return std::make_unique<UnaryExpr>(op,std::move(right));
			}

			return primary();
		}

		std::unique_ptr<Expr> Parser::primary() {
			if (match(TokenType::FALSE)) return std::make_unique<LiteralExpr>(std::make_unique<LoxBool>(false));

			if (match(TokenType::TRUE)) return std::make_unique<LiteralExpr>(std::make_unique<LoxBool>(true));

			if (match(TokenType::NIL)) return std::make_unique<LiteralExpr>(std::make_unique<LoxNil>());

			if (match(TokenType::STRING)) return std::make_unique<LiteralExpr>(std::make_unique<LoxString>(boost::any_cast<std::string>(previous().getLiteral())));

			if (match(TokenType::NUMBER)) return std::make_unique<LiteralExpr>(std::make_unique<LoxDouble>(boost::any_cast<double>(previous().getLiteral())));

			if (match(TokenType::LEFT_PAREN)) {
				auto expr = expression();
				consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
				return std::make_unique<GroupingExpr>(std::move(expr));
			}

			throw error(peek(), "Expect expression.");
		}

		template<typename ...Args>
		bool Parser::match(Args...args) {

			return false;
		}

		bool Parser::check(TokenType type) {
			return false;
		}; // is current token of given type? only peeks, doesn't consume

		Token Parser::advance() {
			return Token();
		}; //consumes the current token, returning it similar to method in Scanner

		Token Parser::consume(TokenType type, const char* message) {
			return Token();
		}

		bool Parser::isAtEnd() {
			return false;
		}; // are we at the end of the file?

		Token Parser::peek() {
			return Token();
		}; // look at the current token without consuming

		Token Parser::previous() {
			return Token();
		};// look at prior token
		
		void Parser::synchronize() {
		
		}; // synchronize to clear out call frames

		Parser::ParseError Parser::error(Token token, const char* message) const {
			
			throw ParseError();
		}
	}
}