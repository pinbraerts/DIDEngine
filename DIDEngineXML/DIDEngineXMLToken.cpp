#include "DIDEngineXMLToken.h"

DIDEngineEnvironment::XMLToken::XMLToken(
	DIDEngineEnvironment::XMLToken::Lexem Type,
	std::wstring Value
) : type(Type), value(Value) {}
