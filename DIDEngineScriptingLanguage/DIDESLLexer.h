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
	DIDESLS_t currentString;
	unsigned lines;
	unsigned pos;

	DIDESLS_t getWord();
	static bool isReservedFunctionWord(DIDESLS_t);
	static bool isType(DIDESLS_t);
	static bool isReservedOperatorWord(DIDESLS_t);
	static bool isBoolLiteral(DIDESLS_t);
	static bool isBinAlpha(DIDESLC_t);
	static bool isOctalAlpha(DIDESLC_t);
	static bool isHexAlpha(DIDESLC_t);
	DIDESLC_t getCharacter();
	DIDESLC_t getCharacterPost();

public:
	struct EOFError {};

	Lexer();
	Lexer(DIDESLS_t);
	void setFile(DIDESLS_t);
	void setString(DIDESLS_t);
	void setStream(std::wistringstream);
	DIDESLS_t getCurrentString();
	unsigned getPos();
	unsigned getLine();
	Token next();
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H
