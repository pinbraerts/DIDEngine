#ifndef DID_ENGINE_LISTENER_H
#define DID_ENGINE_LISTENER_H

#include "DIDEngineDefinitions.h"
#include "DIDEnigneEventArgs.h"
#include "DIDEngineObject.h"

class DIDEngine::EventListener {
private:
	DIDES_t script;
public:
	EventListener(DIDES_t);
	void call(Object*, EventArgs);
};

#endif // !DID_ENGINE_LISTENER_H
