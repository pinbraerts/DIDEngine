#include "DIDESLParcer.h"

DIDESL::Token DIDESL::Parcer::getToken()
{
	try {
		return currentToken = lexer->next();
	} catch (Lexer::EOFError) {
		throw Error(); // unexpected eof
	}
}

DIDESL::Token DIDESL::Parcer::getTokenPost() {
	Token tem = currentToken;
	getToken();
	return tem;
}

#define TYPE_CMP(X) if (currentToken.type == Token::X)
#define THROW_NOCMP(X) if (currentToken.type != Token::X) throw Error()
#define TOKEN_TYPE_CMP TYPE_CMP(OPERATOR_REFERENCE) {\
	append();\
	parceAnnotations();\
	THROW_NOCMP(TYPE);\
	append();\
	parceAnnotations();\
}\
else TYPE_CMP(TYPE) {\
	append();\
	parceAnnotations();\
}

/// <summary>Parses function signature from current token and calls block parce</summary>
bool DIDESL::Parcer::parceFunction() {
	bool isf = false;
	while (currentToken.type == Token::RES_FUNCTION) {
		if (!isf) isf = currentToken.value == L"function";
		parceAnnotations();
		append(); // read qualifiers
	}
	parceAnnotations();
	TYPE_CMP(END) throw Error(); // unexpected
	TOKEN_TYPE_CMP // it's return type
	else if (!isf) throw Error(L"In function declaration must be return type of word \"function\""); // must be return type or word "function"
	TYPE_CMP(NAME) {
		append(); // it's name (unnessesary)
		parceAnnotations();
	}
	TYPE_CMP(OBRACE) {
		append();
		while (true) {
			parceAnnotations();
			TOKEN_TYPE_CMP // type
			else TYPE_CMP(DOTS) {
				append();
				parceAnnotations();
				TYPE_CMP(NAME) {
					append(); // name (unnessesary)
					parceAnnotations();
				}
				TYPE_CMP(COMMA) throw Error(L"Arguments after ..."); // after ... can't be more arguments
				THROW_NOCMP(CBRACE);
				append();
				break;
			}
			else throw Error(L"Expected type of argument"); // type expected
			TYPE_CMP(NAME) {
				append(); // name of arg (unnessesary)
				parceAnnotations();
			}
			TYPE_CMP(COMMA) {
				append();
				continue;
			}
			THROW_NOCMP(CBRACE); // unexpected
			append();
			break;
		}
		parceAnnotations();
	}
	else throw Error(L"In function declaration must be args list"); // in function declaration must be args list
	TYPE_CMP(OCBRACE) {
		parceBlock(); // and some args about functions
		THROW_NOCMP(CCBRACE); // unexpected
		append();
		return true;
	}
	return false; // it's function declaration
}

void DIDESL::Parcer::append() {
	currentTokens.push_back(getTokenPost());
}

/// <summary>Call it everythere</summary>
void DIDESL::Parcer::parceAnnotations() {
	while (currentToken.type == Token::ANNOTATION) {
		append();
		if (getToken().type == Token::OBRACE) parceList();
		// and do smth with annotation
	}
}

/// <summary>Call it if type == }</summary>
void DIDESL::Parcer::parceBlock() {
	append();
	while (currentToken.type != Token::CCBRACE && currentToken.type != Token::END) parceOperator();
}

void DIDESL::Parcer::parceList(Token::Lexem sep) {
	while (currentToken.type != Token::END && currentToken.type != sep) {
		parceExpression(); // and do smth
		if (currentToken.type == Token::COMMA) append();
	}
	if (currentToken.type != sep) throw Error(); // unexpected
	append();
}

/// <summary>From current token</summary>
void DIDESL::Parcer::parceOperator() {
	parceAnnotations();
	switch (currentToken.type) {
	case Token::OCBRACE: // it's complex operator
		parceBlock();
		THROW_NOCMP(CCBRACE);
		append();
		break;
	case Token::RES_OPERATOR: // here some operations for if, while, for, return
		if (currentToken.value == L"return") {
			append();
			parceExpression();
			THROW_NOCMP(SEMICOLON); // unexpected
			append();
		}
		else if (currentToken.value == L"break") {
			// maybe will be cycle identifier
			getToken();
			parceAnnotations();
			THROW_NOCMP(SEMICOLON); // unexpected
			append();
		}
		else if (currentToken.value == L"while") {
			append();
			THROW_NOCMP(OBRACE); // unexpected
			append();
			parceExpression();
			THROW_NOCMP(CBRACE); // unexpected
			append();
			parceAnnotations();
			parceOperator();
		}
		else if (currentToken.value == L"if") {
			append();
			THROW_NOCMP(OBRACE); // unexpected
			append();
			parceExpression();
			THROW_NOCMP(CBRACE); // unexpected
			append();
			parceOperator();
			parceAnnotations();
			if (currentToken.type == Token::RES_OPERATOR && currentToken.value == L"else") {
				append();
				parceOperator();
			}
		}
		else throw Error(); // unexpected
							// TODO: add more operators
		break;
	default:
		TYPE_CMP(OPERATOR_REFERENCE) {
			append();
			parceAnnotations();
			THROW_NOCMP(TYPE);
			append();
			while (true) {
				parceAnnotations();
				if (parceAdd()) { // it's lvalue
					parceAnnotations();
					TYPE_CMP(OPERATOR_SET && currentToken.value == L"=") parceExpression(); // and set it
					else throw Error(L"+=, -=, *=, /=, %= can't be in first declaration");
					parceAnnotations();
					TYPE_CMP(COMMA) {
						append();
						continue;
					}
					TYPE_CMP(SEMICOLON) break;
					throw Error(); // unexpected
				}
			}
		}
		TYPE_CMP(TYPE) {
			append();
			while (true) {
				parceAnnotations();
				if (parceAdd()) { // it's lvalue
					parceAnnotations();
					TYPE_CMP(OPERATOR_SET && currentToken.value == L"=") {
						append();
						parceExpression(); // and set it
					}
					else throw Error(L"+=, -=, *=, /=, %= can't be in first declaration");
					parceAnnotations();
					TYPE_CMP(COMMA) {
						append();
						continue;
					}
					TYPE_CMP(SEMICOLON) break;
					throw Error(); // unexpected
				}
			}
		}
		else parceExpression();
		if (currentToken.type != Token::SEMICOLON) throw Error(); // unexpected
		append();
		break;
	}
}

#define DECLARE_PARCE(CURRENT, CMP, NEXT) bool DIDESL::Parcer::parce##CURRENT() {\
bool res = parce##NEXT();\
if (currentToken.type == Token::OPERATOR_##CMP) {\
	append();\
	parce##CURRENT();\
	return false;\
}\
return res;\
}

bool DIDESL::Parcer::parceExpression() {
	bool res = parceAdd();
	if(currentToken.type == Token::OPERATOR_SET)
		if (res) {
			append();
			parceExpression(); // and set it
			return false;
		}
		else throw Error(L"Value can't be set to non-lvalue argument"); // set to non-lvalue
	return res;
}

DECLARE_PARCE(Add, ADD, Mul)
DECLARE_PARCE(Mul, MUL, BoolOr)
DECLARE_PARCE(BoolOr, BOOL && currentToken.value == L"||", BoolAnd)
DECLARE_PARCE(BoolAnd, BOOL && currentToken.value == L"&&", Bool)
DECLARE_PARCE(Bool, BOOL, BitOr)
DECLARE_PARCE(BitOr, BIT && currentToken.value == L"|", BitAnd)
DECLARE_PARCE(BitAnd, BIT && currentToken.value == L"&", Unary)

bool DIDESL::Parcer::parceUnary() {
	bool res;
	switch (currentToken.type) {
	case Token::OPERATOR_BIT:
		if (currentToken.value == L"~") append();
		res = false;
		break;
	case Token::OPERATOR_BOOL:
		if (currentToken.value == L"!") append();
		res = false;
		break;
	case Token::OPERATOR_REFERENCE:
		append();
	default:
		res = true;
	}
	res = res && parceMember();
	return res;
}

bool DIDESL::Parcer::parceMember(bool first) {
	bool res = first ? parceBasic() : true;
	switch (currentToken.type) {
	case Token::OBRACE:
		if (!res) throw Error(L"Rvalue isn't callable"); // can't call rvalue
		append();
		parceList(); // it's function call
		parceMember(false);
		break;
	case Token::OSBRACE:
		if (!res) throw Error(L"Rvalue isn't indexable"); // can't get index from rvalue
		append();
		parceExpression();
		parceMember(false);
		break;
	case Token::DOT:
		append();
		if(!parceMember(true)) throw Error(L"Name of attribute can't be rvalue"); // name of attribute can't be rvalue
		break;
	}
	return res;
}

bool DIDESL::Parcer::parceBasic() {
	switch (currentToken.type) {
	case Token::OBRACE:
		append();
		parceList();
		return false;
	case Token::BOOL_LITERAL: case Token::NUMBER_LITERAL:
	case Token::NUMBER_LITERAL_BINARY: case Token::NUMBER_LITERAL_OCTAL:
	case Token::NUMBER_LITERAL_MHEX: case Token::STRING_LITERAL:
		append();
		return false;
	case Token::NAME:
		append();
		return true;
	default:
		return false;
	}
}

/*
= parceExpression
+ - parceAdd
* / % parceMul
|| parceBoolOr
&& parceBoolAnd
== != parceBool
| parceBitOr	
& parceBitAnd
$ ~ ! unary + - parceUnary
f() . [] parceMember
(...) name "" 1 true parceBasic
*/

DIDESL::Parcer::Parcer(DIDESLS_t Script) : lexer(new Lexer(Script)), currentTokens() {
	getToken();
}

DIDESL::Parcer::Parcer() : lexer(new Lexer()) {}

void DIDESL::Parcer::setFile(DIDESLS_t path) {
	lexer->setFile(path);
	getToken();
}

DIDESL::DIDESLV_t<DIDESL::Token> DIDESL::Parcer::parce() {
	parceAnnotations();
	TYPE_CMP(START) {
		append();
		parceAnnotations();
	}
	TYPE_CMP(RES_FUNCTION) {
		parceFunction();
		parce();
	}
	TYPE_CMP(END && (currentTokens.empty() || currentTokens.back().type != Token::END)) append();
	return currentTokens;
}

DIDESL::Parcer::Error::Error(DIDESLS_t Message) : message(Message) {}
