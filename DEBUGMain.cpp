#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLLexerTest.h"

int main() {
	DEBUG_SEPARATOR = L"";
	DEBUG_LOG("test #0 ", DIDESLLexerTestFile(0, L"TestScript0.dides", DIDESL::Lexer::Error::UNEXPECTED_EOF, DIDESL::Token::END) ? L"accepted" : L"rejected");
	DEBUG_LOG("test #1 ", DIDESLLexerTest(1, DIDESL::Lexer::Error::EMPTY_LITERAL, DIDESL::Token::OBRACE, 2, 31) ? L"accepted" : L"rejected");
	while (true);
	return 0;
}