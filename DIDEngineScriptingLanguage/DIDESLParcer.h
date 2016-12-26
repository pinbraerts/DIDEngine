#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H

#include "DIDESLDefinitions.h"
#include "DIDESLLexer.h"
#include "DIDESLToken.h"

class DIDESL::Parcer {
private:
	Lexer* lexer;
	Token currentToken;
	DIDESLV_t<Token> currentTokens;
	Token getToken();
	Token getTokenPost();
	void parceFunction();
	void append();
	void parceAnnotations();
	void parceBlock(); // maybe will be DOMAIN args
	void parceArgAfterDots(); // maybe will be TYPE args
	void parceList(Token::Lexem = Token::CBRACE); // maybe arg for separator
	void parceExpression();
	void parceOperator();
	void parceDefinitions();
	void parceNamedExpression();

public:
	struct Error {};
	Parcer(DIDESLS_t);
	DIDESLV_t<Token> parce();

};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
