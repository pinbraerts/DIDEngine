#ifndef DID_ENGINE_EVENT_H

#define DID_ENGINE_EVENT_H

#include "DIDEngineDefinitions.h"
#include <string>

class DIDEngine::Event {
private:
	std::vector<Listener*>;
public:
	Event(DIDES_t = ""); // string of DIDESL -- DID Engine Scripting Language
	void call(EventArgs);
};

#endif // !DID_ENGINE_EVENT_H
