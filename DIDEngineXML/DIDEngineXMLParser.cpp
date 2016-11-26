#include "DIDEngineXMLParser.h"

DIDEngineEnvironment::XMLParser::XMLParser(std::wstring path) : lexer(new DIDEngineEnvironment::XMLLexer(path)), currentToken(lexer->next()) {}

DIDEngineEnvironment::XMLParser::~XMLParser()
{
	delete lexer;
	delete &currentToken;
}

DIDEngineEnvironment::XMLDOMObject* DIDEngineEnvironment::XMLParser::parse() {
	XMLDOMObject* currentDOMObject;
	if (currentToken.type != XMLToken::LBRACE || (currentToken = lexer->next()).type != XMLToken::NAME) throw Error();
	currentDOMObject = new XMLDOMObject(currentToken.value);
	do {
		currentToken = lexer->next();
		switch (currentToken.type) {
		case XMLToken::NAME: {
			std::wstring index = currentToken.value;
			if ((currentToken = lexer->next()).type != XMLToken::TEXT) throw Error();
			currentDOMObject->attributes[index] = currentToken.value;
			continue;
		}
		case XMLToken::RBRACE: break;
		default: throw Error();
		}
		break;
	} while (true);
	if (currentToken.value == L"/>") return currentDOMObject;
	do {
		if ((currentToken = lexer->next()).type == XMLToken::LBRACE) {
			if (currentToken.value == L"</") {
				if ((currentToken = lexer->next()).type != XMLToken::NAME && currentToken.value != currentDOMObject->tagName && (currentToken = lexer->next()).type != XMLToken::RBRACE) throw Error();
				break;
			}
			currentDOMObject->children.push_back(parse());
		}
		else if (currentToken.type == XMLToken::TEXT) currentDOMObject->text += currentToken.value;
	} while (true);
	return currentDOMObject;
}