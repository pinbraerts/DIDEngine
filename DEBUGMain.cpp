#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLParcer.h"
#include <iostream>

int main() {
	DEBUG_USING(SEPARATOR, L"");
	DIDESL::Parcer parcer;
	parcer.setFile(L"DIDEngineScriptingLanguage\\TestScript.dides");
	DIDESL::DIDESLV_t<DIDESL::Token> vec = parcer.parce();
	for (DIDESL::Token tok: vec)
		DEBUG_LOG(DIDESL::Token::toString(tok.type), L": ", L'"', tok.value, L'"');
	DEBUG_STOP_USING(SEPARATOR);
	DEBUG_END_MAIN;
	return 0;
}