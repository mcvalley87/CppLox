#include "Tokens.h"
#include <unordered_map>

namespace Lox {
	namespace Interpreter {

		TokenType Token::getType() const {
			return type;
		}

		void Token::setType(TokenType type) {
			this->type = type;
		}

		std::string Token::getLexeme() const {
			return lexeme;
		}

		void Token::setLexeme(std::string& lexeme) {
			this->lexeme = lexeme;
		}

		boost::any Token::getLiteral() const {
			return literal;
		}

		void Token::setLiteral(boost::any literal) {
			this->literal = literal;
		}

		std::string Token::toString() {
			return  enumStrings.at(type);
		}
	}
}