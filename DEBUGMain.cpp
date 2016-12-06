#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLLexerTest.h"

int main() {
	DEBUG_LOG("test ", test() ? L"accepted" : L"rejected");
	while (true);
	return 0;
}