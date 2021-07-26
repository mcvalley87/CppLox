#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/any.hpp>

namespace Lox {
	namespace Interpreter {
		enum class TokenType {
			// Single-character tokens.
			LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
			COMMA, DOT, MINUS, PLUS, PLUS_PLUS, SEMICOLON, SLASH, STAR,

			// One or two charzcter tokens.
			BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
			GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,
			//Literals.
			IDENTIFIER, STRING, NUMBER,

			// Keywords.
			AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
			PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

			FILE_END
		};

		static const std::unordered_map<TokenType,std::string> enumStrings = {
			{TokenType::LEFT_PAREN,"LEFT_PAREN"},
			{TokenType::RIGHT_PAREN,"RIGHT_PAREN"},
			{TokenType::LEFT_BRACE,"LEFT_BRACE"},
			{TokenType::RIGHT_BRACE,"RIGHT_BRACE"},
			{TokenType::COMMA,"COMMA"},
			{TokenType::DOT,"DOT"},
			{TokenType::MINUS,"MINUS"},
			{TokenType::PLUS,"PLUS"},
			{TokenType::PLUS_PLUS,"PLUS_PLUS"},
			{TokenType::SEMICOLON,"SEMICOLON"},
			{TokenType::SLASH,"SLASH"},
			{TokenType::STAR,"STAR"},

			// One or two character tokens.
			{TokenType::BANG,"BANG"},
			{TokenType::BANG_EQUAL,"BANG_EQUAL"},
			{TokenType::EQUAL,"EQUAL"},
			{TokenType::EQUAL_EQUAL,"EQUAL_EQUAL"},
			{TokenType::GREATER,"GREATER"},
			{TokenType::GREATER_EQUAL,"GREATER_EQUAL"},
			{TokenType::LESS,"LESS"},
			{TokenType::LESS_EQUAL,"LESS_EQUAL"},
			//Literals.
			{TokenType::IDENTIFIER,"IDENTIFIER"},
			{TokenType::STRING,"STRING"},
			{TokenType::NUMBER,"NUMBER"},

			// Keywords.
			{TokenType::AND,"AND"},
			{TokenType::CLASS,"CLASS"},
			{TokenType::ELSE,"ELSE"},
			{TokenType::FALSE,"FALSE"},
			{TokenType::FUN,"FUN"},
			{TokenType::FOR,"FOR"},
			{TokenType::IF,"IF"},
			{TokenType::NIL,"NIL"},
			{TokenType::OR,"OR"},
			{TokenType::PRINT, "PRINT"},
			{TokenType::RETURN,"RETURN"},
			{TokenType::SUPER,"SUPER"},
			{TokenType::THIS,"THIS"},
			{TokenType::TRUE,"TRUE"},
			{TokenType::VAR,"VAR"},
			{TokenType::WHILE,"WHILE"},

			{TokenType::FILE_END,"FILE_END"}
		};

		class Token {
			TokenType type;
			std::string lexeme;
			boost::any literal;
			int line; // line number the token is found on

		public:

			//
			// Constructors
			//
			Token(TokenType t, std::string s, boost::any o, int i)
				: type(t), lexeme(s), literal(o), line(i) {};
			
			Token() = default;

			~Token() = default;

			//
			// Getters and Setters
			//
			TokenType getType() const;
			void setType(TokenType type);

			std::string getLexeme() const;
			void setLexeme(std::string& lexeme);

			boost::any getLiteral() const;
			void setLiteral(boost::any literal);

			int getLine();
			void setLine(int line);

			/*
			// Convert the token to a human readable form
			*/
			std::string toString();

		};

	}
};