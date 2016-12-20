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
	unsigned lines;
	unsigned pos;

	DIDESLS_t getWord();
	bool isReservedFunctionWord(DIDESLS_t);
	bool isType(DIDESLS_t);
	bool isReservedOperatorWord(DIDESLS_t);
	bool isBoolLiteral(DIDESLS_t);
	bool isBinAlpha(DIDESLC_t);
	bool isOctalAlpha(DIDESLC_t);
	bool isHexAlpha(DIDESLC_t);
	DIDESLC_t getCharacter();
	DIDESLC_t getCharacterPost();

public:
	struct EOFError {};

	Lexer();
	Lexer(DIDESLS_t);
	void setFile(DIDESLS_t);
	void setString(DIDESLS_t);
	void setStream(std::wistringstream);
	unsigned getPos();
	unsigned getLines();
	Token next();
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_H
