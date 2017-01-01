#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_DOMAIN_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_DOMAIN_H

#include "DIDESLDefinitions.h"

class DIDESL::Module : DIDESL::DomObject {
private:
	//DIDESLV_t<Function> functions;
	//DIDESLV_t<Line> lines;

public:
	Module(Domain*, unsigned = 0, unsigned = 0);
	int run();

	void addFunction(int = -1);
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_DOMAIN_H