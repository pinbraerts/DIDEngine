#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_FUNCTION_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_FUNCTION_H

#include "DIDESLDefinitions.h"
#include "DIDESLArgument.h"
#include <vector>

class DIDESL::Function {
private:
	Module* parent;
	std::vector<Line*> lines;
	DIDESLBM_t words;
	std::vector<Argument> args;
	DIDESLS_t name;

public:
	enum FunctionWord {
		ASYNC = 1,
		GLOBAL = 2
	};

	Function(DIDESLS_t = L"", std::vector<Line*> = std::vector<Line*>(), std::vector<Argument> = std::vector<Argument>(), DIDESLBM_t = 0, Module* = nullptr);
	DIDESLA_t call(std::vector<Argument>);
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_FUNCTION_H
