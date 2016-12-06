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
	unsigned lines;
	unsigned posInLine;
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
			UNEXPECTED_EOF // info = after, if info = end file insn't opened
		};

		Error(unsigned,
			  unsigned = 0,
			  ErrorType = ErrorType::UNCLASSIFIED,
			  DIDESLS_t = L"Hardcore",
			  Token::Lexem = Token::END);
		DIDESLS_t toString();
		ErrorType type;
		Token::Lexem info;
		DIDESLS_t dir;
		unsigned line;
		unsigned pos;
	};

	Lexer();
	Lexer(DIDESLS_t, DIDESLS_t = L"Hardcore");
	void setFile(DIDESLS_t);
	void setString(DIDESLS_t, DIDESLS_t = L"Hardcore");
	void setStream(std::wistringstream, DIDESLS_t = L"Hardcore");
	Token next();
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H
