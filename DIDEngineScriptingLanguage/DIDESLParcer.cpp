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
#define REFERENCE_CASE case Token::OPERATOR_REFERENCE: append()

/// <summary>Parses function signature from current token and calls block parce</summary>
void DIDESL::Parcer::parceFunction() {
	while (currentToken.type == Token::RES_FUNCTION) currentTokens.push_back(getTokenPost()); // read qualifiers
	switch (currentToken.type) {
	ANNOTATION_CASE;
	case Token::END: throw Error(); // unexpected eof
	REFERENCE_CASE;
	case Token::TYPE:
		append(); // return type (unnecessary)
		parceAnnotations();
	case Token::NAME:
		append(); // identifier (unnecessary)
		parceAnnotations();
	case Token::OBRACE:
		append();
		while (currentToken.type != Token::END && currentToken.type != Token::CBRACE) {
			parceAnnotations();
			switch (currentToken.type) {
			case Token::DOTS: return parceArgAfterDots();
			REFERENCE_CASE;
			case Token::TYPE:
				append(); // it's type
				break;
			default: throw Error(); // Type or ... expected
			}
			switch (currentToken.type) {
			ANNOTATION_CASE;
			case Token::NAME:
				append(); // we know name of arg
				parceAnnotations();
			case Token::COMMA:
				append();
				continue; // next argument
				// maybe . will be such as in C# for classes and ... will be variadic args for got type
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

/// <summary>Call it everythere</summary>
void DIDESL::Parcer::parceAnnotations() {
	while (currentToken.type == Token::ANNOTATION); {
		append();
		if (getToken().type == Token::OBRACE) parceList();
		// and do smth with annotation
	}
}

/// <summary>Call it if type == }</summary>
void DIDESL::Parcer::parceBlock() {
	append();
	while (currentToken.type != Token::CCBRACE) parceOperator();
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
	switch (currentToken.type) {
		ANNOTATION_CASE;
	case Token::OCBRACE: // it's complex operator
		parceBlock();
		break;
	case Token::RES_OPERATOR: // here some operations for if, while, for, return
		if (currentToken.value == L"return") {
			append();
			parceExpression();
			if (currentToken.type != Token::SEMICOLON) throw Error(); // unexpected
			append();
		}
		else if (currentToken.value == L"break") {
			// maybe will be cycle identifier
			getToken();
			parceAnnotations();
			if (currentToken.type != Token::SEMICOLON) throw Error(); // unexpected
			append();
		}
		else if (currentToken.value == L"while") {
			if (getToken().type != Token::OBRACE) throw Error(); // unexpected
			parceExpression();
			if (getToken().type != Token::CBRACE) throw Error(); // unexpected
			parceOperator();
		}
		else if (currentToken.value == L"if") {
			if (getToken().type != Token::OBRACE) throw Error(); // unexpected
			parceExpression();
			if (getToken().type != Token::CBRACE) throw Error(); // unexpected
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
		parceExpression();
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
		else throw Error(); // set to non-lvalue
	return res;
}


DECLARE_PARCE(Add, ADD, Mul)
DECLARE_PARCE(Mul, MUL, BoolOr)
DECLARE_PARCE(BoolOr, BOOL && currentToken.value == L"||", BoolAnd)
DECLARE_PARCE(BoolAnd, BOOL && currentToken.value == L"&&", BitOr)
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
		if (!res) throw Error(); // can't call rvalue
		append();
		parceList(); // it's function call
		parceMember(false);
		break;
	case Token::OSBRACE:
		if (!res) throw Error(); // can't get index from rvalue
		append();
		parceExpression();
		parceMember(false);
		break;
	case Token::DOT:
		if (!res) throw Error(); // can't get attribute of rvalue
		append();
		if(!parceMember(true)) throw Error(); // name of attribute can't be rvalue
		break;
	}
	return res;
}

bool DIDESL::Parcer::parceBasic() {
	bool res;
	switch (currentToken.type) {
	case Token::OBRACE:
		append();
		res = parceExpression();
		if (currentToken.type != Token::CBRACE) throw Error(); // unexpected
		break;
	case Token::BOOL_LITERAL: case Token::NUMBER_LITERAL:
	case Token::NUMBER_LITERAL_BINARY: case Token::NUMBER_LITERAL_OCTAL:
	case Token::NUMBER_LITERAL_MHEX: case Token::STRING_LITERAL:
		append();
		return false;
		break;
	case Token::NAME:
		append();
		return true;
		break;
	}
	return res;
}

/*
= parceExpression
+ - parceAdd
* / % parceMul
|| parceBoolOr
&& parceBoolAnd
| parceBitOr	
& parceBitAnd
$ ~ ! unary + - parceUnary
f() . [] parceMember
(...) name "" 1 true parceBasic
*/

/*
void DIDESL::Parcer::parceExpression() {
	switch (currentToken.type) {
	ANNOTATION_CASE;
	REFERENCE_CASE;
	case Token::OBRACE:
		append();
		parceExpression();
		if (currentToken.type != Token::CBRACE) throw Error(); // unexpected
	case Token::TYPE:
		parceDefinitions();
		return;
	case Token::NAME:
		append();
		parceNamedExpression();
		if (currentToken.type == Token::OPERATOR_SET) {
			append();
			return parceExpression(); // and set it to current token
		}
		break;
	case Token::BOOL_LITERAL: case Token::NUMBER_LITERAL:
	case Token::NUMBER_LITERAL_BINARY: case Token::NUMBER_LITERAL_OCTAL:
	case Token::NUMBER_LITERAL_MHEX: case Token::STRING_LITERAL:
		append();
		break;
	default: throw Error();
	}
	switch (currentToken.type) {
	case Token::OPERATOR_ARITHMETIC:
		append();
		return parceExpression(); // and smth with current expression
	}
}

void DIDESL::Parcer::parceDefinitions() {
	switch (currentToken.type) {
	ANNOTATION_CASE;
	case Token::NAME:
		append();
		break;
	case Token::SEMICOLON: return;
	default: throw Error(); // name expected
	}
	switch (currentToken.type) {
	ANNOTATION_CASE;
	case Token::OPERATOR_SET:
		if (currentToken.value != L"=") throw Error(); // it's first declaration
		append();
		parceExpression(); // and set it to current token
	case Token::COMMA:
		append();
		return parceDefinitions();
	}
}

void DIDESL::Parcer::parceNamedExpression() {
	switch (currentToken.type) {
	case Token::OBRACE:
		append(); // it's function call
		parceList(Token::CBRACE);
		if (currentToken.type != Token::CBRACE) throw Error(); // unexpected
	case Token::DOT:
		append();
		if (currentToken.type != Token::NAME) throw Error(); // expected name
		parceNamedExpression();
	}
}*/

DIDESL::Parcer::Parcer(DIDESLS_t Script) : lexer(new Lexer(Script)), currentTokens() {
	getToken();
}

DIDESL::DIDESLV_t<DIDESL::Token> DIDESL::Parcer::parce() {
	switch (currentToken.type) {
	ANNOTATION_CASE;
	case Token::START:
		currentTokens.push_back(currentToken);
		getToken();
		parceAnnotations(); // go to next token
	case Token::END: return currentTokens;
	case Token::RES_FUNCTION:
		parceFunction();
		return parce();
	}
}
