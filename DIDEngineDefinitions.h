#ifndef DID_ENGINE_DEFINITIONS_H

#define DID_ENGINE_DEFINITIONS_H
#define DEBUGGING

#include "DEBUG.h"
#include "DIDEngineXML/DIDEngineEnvironment.h"

namespace DIDEngine {
	typedef signed char DIDEOPV_t;
	typedef unsigned short DIDEID_t;
	typedef std::wstring DIDES_t;
	typedef short DIDEI_t;
	class Event;
	class EventListener;
	class EventArgs;
	class Object;
	class ObjectProperty;
	class ObjectAction;
}

#endif // !DID_ENGINE_DEFINITIONS