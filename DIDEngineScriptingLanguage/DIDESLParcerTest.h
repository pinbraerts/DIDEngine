#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_PARSER_TEST_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_PARSER_TEST_H

#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING

#include "../DEBUG.h"
#include "DIDESLParcer.h"

static unsigned __tests = 1;

bool testFile(DIDESL::DIDESLS_t file, DIDESL::DIDESLS_t msg = L"") {
	DEBUG_USING(PREFIX, (DIDESL::DIDESLS_t)L"TEST no." + std::to_wstring(__tests) + L": ", SEPARATOR, L": ");
	++__tests;
	try {
		DIDESL::Parcer parcer;
		parcer.setFile(file);
		DIDESL::DIDESLV_t<DIDESL::Token> vec = parcer.parce();
		for (DIDESL::Token tok : vec)
			DEBUG_LOG(DIDESL::Token::toString(tok.type), L'"' + tok.value + L'"');
	}
	catch (DIDESL::Parcer::Error e) {
		DEBUG_LOG(e.message);
		DEBUG_STOP_USING(PREFIX, SEPARATOR);
		return e.message == msg;
	}
	DEBUG_STOP_USING(PREFIX, SEPARATOR);
	return msg.empty();
}

void logTest(DIDESL::DIDESLS_t file, DIDESL::DIDESLS_t msg=L"") {
	DEBUG_USING(PREFIX, (DIDESL::DIDESLS_t)L"TEST no." + std::to_wstring(__tests) + L": ", SEPARATOR, L"");
	DEBUG_LOG(testFile(file, msg) ? L"passed" : L"failed", L"!\n");
	DEBUG_WAIT(L"Press Enter to finish test... ");
	__DEBUG_PREFIX = L"";
	DEBUG_LOG();
	DEBUG_STOP_USING(SEPARATOR, PREFIX);
}

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_PARSER_TEST_H