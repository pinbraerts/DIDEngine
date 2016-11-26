#include "DIDEngineXMLDOMObject.h"

DIDEngineEnvironment::XMLDOMObject::XMLDOMObject(std::wstring TagName,
	std::wstring Text,
	std::map<std::wstring, std::wstring> Attributes,
	std::vector<DIDEngineEnvironment::XMLDOMObject*> Children
	) : tagName(TagName), text(Text), attributes(Attributes), children(Children) {}

std::wstring DIDEngineEnvironment::XMLDOMObject::toString(unsigned tabs) {
	std::wstring str = L"";
	std::wstring tabString = L"";
	for (unsigned i = 0; i < tabs; ++i) tabString += '\t';
	str += tabString + L"<" + tagName;
	for (std::pair<std::wstring, std::wstring> attr : attributes) str += L" " + attr.first + L" = \"" + attr.second + L"\"";
	if (children.size() == 0 && text.size() == 0) return str + L"/>";
	str += '>';
	for (XMLDOMObject* child : children) str += L"\n" + child->toString(tabs + 1);
	if (text.size() != 0) str += L"\n" + tabString + text;
	str += L"\n" + tabString + L"</" + tagName + L">";
	return str;
}