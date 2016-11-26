#ifndef DID_ENGINE_XML_LEXER_H
#define DID_ENGINE_XML_LEXER_H

#include "DIDEngineEnvironmentDefinitions.h"
#include "DIDEngineXMLToken.h"
#include <fstream>
#include <string>

class DIDEngineEnvironment::XMLLexer {
public:
	XMLLexer(std::wstring);
	DIDEngineEnvironment::XMLToken next();
	~XMLLexer();

	class Error {};

private:
	std::wifstream *file;
	wchar_t currentCharacter;
	XMLToken::Lexem currentLexem;
};

#endif // !DID_ENGINE_XML_LEXER_H
