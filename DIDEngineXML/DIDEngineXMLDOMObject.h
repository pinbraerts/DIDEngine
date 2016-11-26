#ifndef DID_ENGINE_XML_DOM_OBJECT
#define DID_ENGINE_XML_DOM_OBJECT

#include "DIDEngineEnvironmentDefinitions.h"
#include <string>
#include <map>
#include <vector>

struct DIDEngineEnvironment::XMLDOMObject {
	XMLDOMObject(std::wstring,
		std::wstring = L"",
		std::map<std::wstring, std::wstring> = std::map<std::wstring, std::wstring>(),
		std::vector<XMLDOMObject*> = std::vector<XMLDOMObject*>()
		);

	std::wstring tagName;
	std::map<std::wstring, std::wstring> attributes;
	std::wstring text;
	std::vector<XMLDOMObject*> children;

	std::wstring toString(unsigned = 0);
};

#endif // !DID_ENGINE_XML_DOM_OBJECT