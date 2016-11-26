#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H

#include "DIDESLDefinitions.h"
#include "DIDESLLexer.h"
#include "DIDESLToken.h"
#include <string>

class DIDESL::Parcer {
private:
	Lexer* lexer;
	Token currentToken;
public:
	Parcer(DIDESLS_t Script) : lexer(new Lexer(Script)), currentToken(lexer->next()) {};
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
