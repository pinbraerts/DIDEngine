#include "DIDEnigneEventArgs.h"

DIDEngine::EventArgs::EventArgs(std::vector<DIDEI_t> INTS, std::vector<DIDES_t> STRS, std::vector<DIDEID_t> IDS) : Ints(INTS), Strs(STRS), IDs(IDS) {}

DIDEngine::DIDES_t DIDEngine::EventArgs::getString(unsigned index) {
	return Strs[index];
}

DIDEngine::DIDES_t DIDEngine::EventArgs::popString() {
	DIDES_t str = Strs.back();
	Strs.pop_back();
	return str;
}

DIDEngine::DIDEID_t DIDEngine::EventArgs::getgId(unsigned index) {
	return IDs[index];
}

DIDEngine::DIDEID_t DIDEngine::EventArgs::popId() {
	DIDEID_t id = IDs.back();
	IDs.pop_back();
	return id;
}

DIDEngine::DIDEI_t DIDEngine::EventArgs::getInteger(unsigned index) {
	return Ints[index];
}

DIDEngine::DIDEI_t DIDEngine::EventArgs::popInteger() {
	DIDEI_t in = Ints.back();
	Ints.pop_back();
	return in;
}
