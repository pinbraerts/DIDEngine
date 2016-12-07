#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_TEST
#define DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_TEST

#include "DIDESLLexer.h"
#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING
#include "../DEBUG.h"

#define DIDESLLexerTest(NUMBER, TYPE, INFO, LINE, POS) DIDESLLexerTestFile(NUMBER, L"DIDEngineScriptingLanguage/TestScript" L###NUMBER L".dides", TYPE, INFO, LINE, POS)

void readScript(DIDESL::Lexer& lex) {
	DIDESL::Token tok = lex.next();
	while (tok.type != DIDESL::Token::END) {
		DEBUG_LOG(DIDESL::Token::toString(tok.type), L": ", L'"', tok.value, L'"');
		tok = lex.next();
	}
}

bool DIDESLLexerTestFile(unsigned number,
						 DIDESL::DIDESLS_t dir,
						 int type = -1,
						 int info = -1,
						 unsigned line = 1,
						 unsigned pos = 0) {
	DEBUG_USING_SEPARATOR(L"");
	DEBUG_USING_PREFIX((DIDESL::DIDESLS_t)L"TEST #" + std::to_wstring(number) + L": ");
	DIDESL::Lexer lex;
	try {
		lex.setFile(dir);
		readScript(lex);
	}
	catch (DIDESL::Lexer::Error e) {
		DEBUG_LOG(e.toString());
		DEBUG_STOP_USING_PREFIX;
		DEBUG_STOP_USING_SEPARATOR;
		return (type < 0 || e.type == type) && (info < 0 || e.info == info) && e.pos == pos && e.line == line && e.dir == dir;
	}
	DEBUG_STOP_USING_PREFIX;
	DEBUG_STOP_USING_SEPARATOR;
	return false;
}

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_LEXER_TEST