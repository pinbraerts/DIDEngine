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
	std::wistringstream scriptStream;
	DIDESLC_t currentCharacter;
	Token::Lexem currentLexem;

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
	class Error {};

	Lexer();
	Lexer(DIDESLS_t);
	void setFile(DIDESLS_t);
	Token next();
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H
