#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLParcerTest.h"
#include <iostream>

int main() {
	logTest(L"DIDEngineScriptingLanguage\\TestScript.dides");
	logTest(L"DIDEngineScriptingLanguage\\TestScpt.dides", L"Error (code: 1): file \"DIDEngineScriptingLanguage\\TestScpt.dides\" is invalid!");
	logTest(L"DIDEngineScriptingLanguage\\TestScript1.dides");
	DEBUG_END_MAIN;
	return 0;
}