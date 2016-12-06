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
		BOOL_LITERAL,

		// reserved words
		RES_FUNCTION, // function, async, global
		RES_OPERATOR, // while, if, return, break

		// operators
		OPERATOR_ARITHMETIC, // +, -, *, /, %
		OPERATOR_SET, // =, +=, -=, *=, /=
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

		END,
		NONE
	};

	Lexem type;
	DIDESLS_t value;

	Token(Lexem Type, DIDESLS_t Value) : type(Type), value(Value) {};
	Token(Lexem Type, DIDESLC_t Ch) : type(Type) {
		value = (DIDESLS_t)L"" + Ch;
	};
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_TOKEN_H
