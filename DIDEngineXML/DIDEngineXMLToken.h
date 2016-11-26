#ifndef DID_ENGINE_XML_TOKEN

#define DID_ENGINE_XML_TOKEN
#include "DIDEngineEnvironmentDefinitions.h"
#include <string>

struct DIDEngineEnvironment::XMLToken {
	enum Lexem {
		START,
		END,
		RBRACE,
		LBRACE,
		TEXT,
		NAME
	};

	XMLToken(Lexem = START, std::wstring = L"");
	Lexem type;
	std::wstring value;
};

#endif // !DID_ENGINE_XML_TOKEN
