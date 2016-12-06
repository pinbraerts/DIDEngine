#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_TEST
#define DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_TEST

#include "DIDESLLexer.h"
#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING
#include "../DEBUG.h"

void readScript(DIDESL::Lexer& lex) {
	DIDESL::Token tok = lex.next();
	while (tok.type != DIDESL::Token::END) {
		DEBUG_LOG(L'"', tok.value, L'"');
		tok = lex.next();
	}
}

bool test() {
	DEBUG_SEPARATOR = L"";
	DIDESL::Lexer lex;
	lex.setFile(L"DIDEngineScriptingLanguage/TestScript.dides");
	try {
		readScript(lex);
	}
	catch (DIDESL::Lexer::Error e) {
		DEBUG_LOG(e.toString());
		return e.type == DIDESL::Lexer::Error::EMPTY_LITERAL && e.info == DIDESL::Token::OBRACE && e.pos == 31 && e.line == 2 && e.dir == L"DIDEngineScriptingLanguage/TestScript.dides";
	}
	return false;
}

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_TEST