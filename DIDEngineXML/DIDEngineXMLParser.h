#ifndef DID_ENGINE_XML_PARSER_H
#define DID_ENGINE_XML_PARSER_H

#include "DIDEngineEnvironmentDefinitions.h"
#include "DIDEngineXMLToken.h"
#include "DIDEngineXMLLexer.h"
#include "DIDEngineXMLDOMObject.h"
#include <string>

class DIDEngineEnvironment::XMLParser {
private:
	XMLLexer* lexer;
	XMLToken currentToken;

public:
	class Error {};

	XMLParser(std::wstring);
	~XMLParser();
	XMLDOMObject* parse();
};

#endif // !DID_ENGINE_XML_PARSER_H
