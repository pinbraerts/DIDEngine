#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_ARGUMENT_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_ARGUMENT_H

#include "DIDESLDefinitions.h"

struct DIDESL::Argument {
	DIDESLS_t name;
	DIDESLS_t value;
	Type type;

	Argument(Type Type, DIDESLS_t Name, DIDESLS_t Value) : type(Type), name(Name), value(Value) {};
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_ARGUMENT_H
