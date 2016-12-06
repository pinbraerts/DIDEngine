#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H

#include "DIDESLDefinitions.h"
#include "DIDESLToken.h"
#include <string>
#include <sstream>
#include <fstream>

class DIDESL::Lexer
{
private:
	std::wistringstream script;
	DIDESLC_t currentCharacter;
	Token::Lexem currentLexem;
	DIDESLS_t dir;

	DIDESLS_t getWord();
	bool isReservedFunctionWord(DIDESLS_t);
	bool isType(DIDESLS_t);
	bool isReservedOperatorWord(DIDESLS_t);
	bool isBoolLiteral(DIDESLS_t);
	Token getAnnotation();
	DIDESLC_t getCharacter();
	DIDESLC_t getCharacterPost();
	bool ignoreSpaces(bool = false);
	Token getLiteral(bool = false, bool = false, bool = true);

public:
	struct Error {
		enum ErrorType {
			UNCLASSIFIED = 0, // info = after
			EMPTY_LITERAL, // info = after
			UNEXPECTED_LITERAL, // info = literal
			EXPECTED_LITERAL, // info = literal
			UNEXPECTED_EOF // info = after
		};

		Error(unsigned Start, ErrorType Typet = ErrorType::UNCLASSIFIED, DIDESLS_t Dir = L"Hardcore", Token::Lexem Info = Token::END) : start(Start), type(Typet), dir(Dir), info(Info) {};
		DIDESLS_t toString() {
			std::wstringstream stream;
			if (type != UNCLASSIFIED) {
				stream << L"Error: ";
				switch (type) {
				case EMPTY_LITERAL:
					stream << L"empty literal after ";
					break;
				case UNEXPECTED_LITERAL:
					stream << L"unexpected ";
					break;
				case EXPECTED_LITERAL:
					stream << L"expected ";
					break;
				case UNEXPECTED_EOF:
					stream << L"unexpected end of file after ";
					break;
				}
			}
			else stream << L"Unclassified error after ";
			stream << Token::toString(info) << L" on " << start << L" position in \"" << dir << L"\"!";
			return stream.str();
		}
		ErrorType type; // ErrorType and Token::Lexem
		Token::Lexem info;
		DIDESLS_t dir;
		unsigned start;
	};

	Lexer();
	Lexer(DIDESLS_t, DIDESLS_t = L"Hardcore");
	void setFile(DIDESLS_t);
	void setString(DIDESLS_t, DIDESLS_t = L"Hardcore");
	void setStream(std::wistringstream, DIDESLS_t = L"Hardcore");
	Token next();
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H
