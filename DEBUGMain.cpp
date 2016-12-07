#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLLexerTest.h"
#include <iostream>

int main() {
	DEBUG_USING_SEPARATOR(L"");
	DEBUG_LOG(L"test #0 ", DIDESLLexerTestFile(0, L"TestScript0.dides", DIDESL::Lexer::Error::UNEXPECTED_EOF, DIDESL::Token::END) ? L"accepted" : L"rejected");
	DEBUG_LOG(L"test #1 ", DIDESLLexerTest(1, DIDESL::Lexer::Error::EMPTY_LITERAL, DIDESL::Token::OBRACE, 2, 31) ? L"accepted" : L"rejected");
	std::cout << "Press any key to quit... ";
	std::string res;
	std::getline(std::cin, res);
	DEBUG_STOP_USING_SEPARATOR;
	return 0;
}