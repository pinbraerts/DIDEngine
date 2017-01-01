#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H

#include "DIDESLDefinitions.h"
#include "DIDESLLexer.h"
#include "DIDESLToken.h"

class DIDESL::Parcer {
public:
	struct Error {
		enum Code {
			RVALUE_DECLARATION,
			INVALID_FILE,
			ATTR_RVALUE,
			INDEX_RVALUE,
			CALL_RVALUE,
			SET_TO_NON_LVALUE,
			WRONG_DECLARATION,
			NO_LIST_IN_FUNC,
			ARGS_AFTER_DOTS,
			WRONG_FUNCTION,
			UNEXPECTED
		};

		Error(const Parcer*, Code=UNEXPECTED);
		const DIDESLS_t message;
	};

	Parcer(DIDESLS_t, DIDESLS_t=L"Hardcore");
	Parcer();

	void setString(DIDESLS_t, DIDESLS_t=L"Hardcore");
	void setFile(DIDESLS_t);
	DIDESLV_t<Token> parce();

private:
	Lexer* lexer;
	Token currentToken;
	DIDESLV_t<Token> currentTokens;
	DIDESLS_t file;
	Token getToken();
	Token getTokenPost();

	DIDESLS_t errorMessage(Error::Code) const;
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
	bool parceMember(bool = true);
	bool parcePrimary();

};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_PARCER_H
