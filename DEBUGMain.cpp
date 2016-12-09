#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLLexerTest.h"
#include <iostream>

int main() {
	DEBUG_USING(SEPARATOR, L"");
	DEBUG_LOG(L"test #0 ", DIDESLLexerTestFile(0, L"TestScript0.dides", DIDESL::Lexer::Error::UNEXPECTED_EOF, DIDESL::Token::END) ? L"accepted" : L"rejected");
	DIDESL_LEXER_TEST_EXECUTE_AND_PRINT(1, DIDESL::Lexer::Error::EMPTY_LITERAL, DIDESL::Token::OBRACE, 2, 31);
	DEBUG_END_MAIN;
	DEBUG_STOP_USING(SEPARATOR);
	return 0;
}