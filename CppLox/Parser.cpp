#include "Parser.h"

namespace Lox {
	namespace Interpreter {

		Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
			//std::cout << "Starting Parser..." << std::endl;
			//std::cout << "Number of Tokens: " << this->tokens.size() << std::endl;
		};

		/*std::unique_ptr<Expr> Parser::parse() {
			try {
				return expression();
			}
			catch (ParseError error) {
				return nullptr;
			}
		}*/

		std::vector<std::unique_ptr<Stmt>> Parser::parse() {
			std::vector<std::unique_ptr<Stmt>> statements;

			while (!isAtEnd()) {
				statements.push_back(declaration());
			}

			return statements;
		}
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

			while (match(TokenType::MINUS, TokenType::PLUS, TokenType::PLUS_PLUS)) {
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

			if (match(TokenType::IDENTIFIER)) return std::make_unique<VariableExpr>(previous());

			if (match(TokenType::LEFT_PAREN)) {
				auto expr = expression();
				consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
				return std::make_unique<GroupingExpr>(std::move(expr));
			}

			throw error(peek(), "Expect expression.");
		}

	//		STATEMENT RELATED PARSING

		std::unique_ptr<Stmt> Parser::statement() {
			try {
				if (match(TokenType::PRINT)) return printStatement();

				return expressionStatement();
			}
			catch (ParseError pError) {
				synchronize();
				return nullptr;
			}
		}

		std::unique_ptr<Stmt> Parser::printStatement() {
			auto value = expression();
			consume(TokenType::SEMICOLON, "Expect ';' after value.");
			return std::make_unique<PrintStmt>(std::move(value));
		}

		std::unique_ptr<Stmt> Parser::expressionStatement() {
			auto value = expression();
			consume(TokenType::SEMICOLON, "Expect ';' after Expression.");
			return std::make_unique<ExpressionStmt>(std::move(value));
		}

		//		DECLARATION RELATED PARSING

		std::unique_ptr<Stmt> Parser::declaration() {
			try {
				if (match(TokenType::VAR)) return varDeclaration();

				return statement();
			}
			catch (ParseError pErr) {
				synchronize(); // clear out that callstack
				return nullptr;
			}
		}

		std::unique_ptr<Stmt> Parser::varDeclaration() {
			Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

			std::unique_ptr<Expr> expr = nullptr;

			if (match(TokenType::EQUAL)) expr = expression();

			consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
			return std::make_unique<VariableStmt>(name, std::move(expr));
		}

		// HELPER FUNCTIONS


		template<typename ...Args>
		bool Parser::match(Args...args) {
			std::initializer_list<bool> results{ check(args)... };
			for (auto r : results) {
				if (r) {
					advance();
					return true;
				}
			}
			return false;
		}

		bool Parser::check(TokenType type) const {
			if (isAtEnd()) {
				return false;
			}
			return peek().getType() == type;
		}; // is current token of given type? only peeks, doesn't consume

		Token Parser::advance() {

			if (!isAtEnd()) { ++current; }
			return previous();
			return Token();
		}; //consumes the current token, returning it similar to method in Scanner

		Token Parser::consume(TokenType type, const char* message) {

			if (check(type)) { return advance(); }

			throw error(peek(), message);
		}

		bool Parser::isAtEnd() const {
			return peek().getType() == TokenType::FILE_END;
		}; // are we at the end of the file?

		Token Parser::peek() const {
			return tokens.at(current);
		}; // look at the current token without consuming

		Token Parser::previous() const {
			return tokens.at(current - 1);
		};// look at prior token
		
		void Parser::synchronize() {
		
			advance();
			std::cout << "hello there" << std::endl;
			while (!isAtEnd()) {
				if (previous().getType() == TokenType::SEMICOLON) {
					return;
				}

				switch (peek().getType()) {
				case TokenType::CLASS:
				case TokenType::FUN:
				case TokenType::VAR:
				case TokenType::FOR:
				case TokenType::IF:
				case TokenType::WHILE:
				case TokenType::PRINT:
				case TokenType::RETURN:
					return;
				default:
					break;
				}

				advance();
			}
		}; // synchronize to clear out call frames

		Parser::ParseError Parser::error(Token token, const char* message) const {
			
			Lox::Interpreter::Interpreter::error(token, message);
			throw ParseError{};
		}
	}
}