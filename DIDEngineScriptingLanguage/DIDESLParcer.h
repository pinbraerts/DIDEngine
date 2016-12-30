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
	bool parceFunction();
	void append();
	void parceAnnotations();
	void parceBlock(); // maybe will be DOMAIN args
	void parceArgsAfterDots(); // maybe will be TYPE args
	void parceList(Token::Lexem = Token::CBRACE); // maybe arg for separator
	void parceOperator();
	bool parceExpression();
	bool parceAdd();
	bool parceMul();
	bool parceBoolAnd();
	bool parceBoolOr();
	bool parceBool();
	bool parceBitOr();
	bool parceBitAnd();
	bool parceUnary();
	bool parceMember(bool=true);
	bool parceBasic();

public:
	struct Error {
		Error(DIDESLS_t=L"Unexpected");
		const DIDESLS_t message;
	};
	Parcer(DIDESLS_t);
	Parcer();
	void setFile(DIDESLS_t);
	DIDESLV_t<Token> parce();

};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
