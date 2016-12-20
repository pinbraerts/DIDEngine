#include "DIDESLParcer.h"

DIDESL::Token DIDESL::Parcer::getToken()
{
	try {
		return currentToken = lexer->next();
	} catch (Lexer::EOFError e) {
		throw Error(); // unexpected eof
	}
}

DIDESL::Token DIDESL::Parcer::getTokenPost() {
	Token tem = currentToken;
	getToken();
	return tem;
}

#define ANNOTATION_CASE case Token::ANNOTATION: parceAnnotations()

/// <summary>Parses function signature from current token</summary>
void DIDESL::Parcer::parceFunction() {
	while (currentToken.type == Token::RES_FUNCTION) currentTokens.push_back(getTokenPost()); // read qualifiers
	switch (currentToken.type) {
	case Token::END: throw Error(); // unexpected eof
	case Token::TYPE: append(); // return type (unnecessary)
	case Token::NAME: append(); // identifier (unnecessary)
	ANNOTATION_CASE;
	case Token::OBRACE:
		getToken();
		while (currentToken.type != Token::END && currentToken.type != Token::CBRACE) {
			if (currentToken.type == Token::ANNOTATION) parceAnnotations();
			if (currentToken.type == Token::OPERATOR_ENVIRONMENT) {
				if (currentToken.value != L"...") throw Error(); // expected ')' or TYPE or ... or @
				return parceArgAfterDots();
			}
			else if (currentToken.type != Token::TYPE) throw Error(); // expected ')' or TYPE or ... or @
			switch (getToken().type) {
			case Token::NAME: append(); // we know name of arg
			case Token::OPERATOR_ENVIRONMENT:
				if (currentToken.value == L",") {
					append();
					continue; // next argument
				}
				else throw Error(); // unexpected (maybe . will be such as in C# for classes and ... will be variadic args for got type)
			case Token::CBRACE:
				append();
				continue; // end of cycle
			default: throw Error(); // unexpected
			}
		}
		if (currentToken.type == Token::END) throw Error(); // unexpected
		append();
		parceAnnotations();
		if (currentToken.type == Token::OCBRACE) return parceBlock(); // and some args about function
	default: throw Error(); // unexpected
	}
}

void DIDESL::Parcer::append() {
	currentTokens.push_back(getTokenPost());
}

void DIDESL::Parcer::parceAnnotations() {
	while (currentToken.type == Token::ANNOTATION); {
		append();
		if (getToken().type == Token::OBRACE) parceList();
		// and do smth with annotation
	}
}

/// <summary>Call if value == ...</summary>
void DIDESL::Parcer::parceArgAfterDots() {
	append(); // it's variadic arguments function
	switch (getToken().type) {
	case Token::NAME: append(); // we know package's name
								// after '...' won't be more args (maybe)
		ANNOTATION_CASE; // but could be annotation
	case Token::CBRACE:
		append();
		return parceBlock(); // parce { }
	default: throw Error(); // unexpected current token
	}
}

void DIDESL::Parcer::parceList() {
	while (currentToken.type != Token::CBRACE /*separator*/) {
		parceExpression(); // and do smth
		if (currentToken.type == Token::OPERATOR_ENVIRONMENT && currentToken.value == L",") append();
	}
}

DIDESL::Parcer::Parcer(DIDESLS_t Script) : lexer(new Lexer(Script)), currentTokens() {
	getToken();
}

DIDESL::DIDESLV_t<DIDESL::Token> DIDESL::Parcer::parce() {
	switch (currentToken.type) {
	case Token::START: currentTokens.push_back(currentToken); getToken();
	case Token::END: return currentTokens;
	case Token::RES_FUNCTION:
		parceFunction();
		return parce();
	}
}
