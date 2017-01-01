#ifndef DID_ENGINE_EVENT_ARGS_H
#define DID_ENGINE_EVENT_ARGS_H

#include "DIDEngineDefinitions.h"
#include <vector>

class DIDEngine::EventArgs {
private:
	std::vector<DIDEID_t> IDs;
	std::vector<DIDEI_t> Ints;
	std::vector<DIDES_t> Strs;

public:
	EventArgs(
		std::vector<DIDEI_t> = std::vector<DIDEI_t>(),
		std::vector<DIDES_t> = std::vector<DIDES_t>(),
		std::vector<DIDEID_t> = std::vector<DIDEID_t>()
	);

	DIDES_t getString(unsigned);
	DIDES_t popString();
	DIDEID_t getgId(unsigned);
	DIDEID_t popId();
	DIDEI_t getInteger(unsigned);
	DIDEI_t popInteger();
};

#endif // !DID_ENGINE_EVENT_ARGS_H
