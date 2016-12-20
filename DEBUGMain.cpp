#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLLexer.h"
#include <iostream>

int main() {
	DEBUG_USING(SEPARATOR, L"");
	DIDESL::Lexer lex;
	lex.setFile(L"DIDEngineScriptingLanguage\\TestScript1.dides");
	DIDESL::Token tok = lex.next();
	while (tok.type != DIDESL::Token::END) {
		DEBUG_LOG(DIDESL::Token::toString(tok.type), L": ", L'"', tok.value, L'"');
		tok = lex.next();
	}
	DEBUG_STOP_USING(SEPARATOR);
	DEBUG_END_MAIN;
	return 0;
}