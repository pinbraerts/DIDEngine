#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "DEBUG.h"
#include "DIDEngineScriptingLanguage\DIDESLParcerTest.h"
#include <iostream>

int main() {
	logTest(L"DIDEngineScriptingLanguage\\TestScript.dides");
	logTest(L"DIDEngineScriptingLanguage\\TestScpt.dides", (DIDESL::DIDESLS_t)L"Error (code: " + std::to_wstring(DIDESL::Parcer::Error::INVALID_FILE) + L"): file \"DIDEngineScriptingLanguage\\TestScpt.dides\" is invalid!");
	logTest(L"DIDEngineScriptingLanguage\\TestScript1.dides");
	logTest(L"DIDEngineScriptingLanguage\\TestScript2.dides");
	DEBUG_END_MAIN;
	return 0;
}