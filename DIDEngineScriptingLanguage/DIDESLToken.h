#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_TOKEN_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_TOKEN_H

#include "DIDESLDefinitions.h"
#include <string>

struct DIDESL::Token
{
	enum Lexem {
		START,
		TYPE,
		SEMICOLON,
		NAME,

		// literals
		STRING_LITERAL,
		NUMBER_LITERAL,
		NUMBER_LITERAL_BINARY,
		NUMBER_LITERAL_OCTAL,
		NUMBER_LITERAL_MHEX,
		BOOL_LITERAL,

		// reserved words
		RES_FUNCTION, // function, async, global
		RES_OPERATOR, // while, if, return, break

		// operators
		OPERATOR_ARITHMETIC, // +, -, *, /, %
		OPERATOR_SET, // =, +=, -=, *=, /=, %=
		OPERATOR_BIT, // |, &, ^, ~
		OPERATOR_BOOL, // &&, ||, !, ==, !=, >, >=, <, <=
		OPERATOR_ENVIRONMENT, // ..., ,, .
		OPERATOR_REFERENCE, // $

		// braces
		CBRACE, // )
		OBRACE, // (
		CSBRACE, // ]
		OSBRACE, // [
		CCBRACE, // }
		OCBRACE, // {

		ANNOTATION, // @

		END
	};

	Lexem type;
	DIDESLS_t value;

	static DIDESLS_t toString(Lexem lexem) {
		switch (lexem) {
		case START:
			return L"start";
		case TYPE:
			return L"type literal";
		case SEMICOLON:
			return L"semicolon";
		case NAME:
			return L"identifier literal";
		case STRING_LITERAL:
			return L"string literal";
		case NUMBER_LITERAL:
			return L"number literal";
		case BOOL_LITERAL:
			return L"boolean literal";
		case RES_FUNCTION:
			return L"reserved function word";
		case RES_OPERATOR:
			return L"reserved operator word";
		case OPERATOR_ARITHMETIC: case OPERATOR_BIT: case OPERATOR_BOOL: case OPERATOR_ENVIRONMENT: case OPERATOR_REFERENCE: case OPERATOR_SET:
			return L"operator";
		case OBRACE: case CBRACE: case OSBRACE: case CSBRACE: case OCBRACE: case CCBRACE:
			return L"brace";
		case END:
			return L"end";
		}
		return L"none";
	}

	Token() {};
	Token(Lexem Type, DIDESLS_t Value) : type(Type), value(Value) {};
	Token(Lexem Type, DIDESLC_t Ch) : type(Type) {
		value = (DIDESLS_t)L"" + Ch;
	};
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_TOKEN_H
