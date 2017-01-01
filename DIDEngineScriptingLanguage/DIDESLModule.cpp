#include "DIDESLModule.h"

DIDESL::Module::Module(DIDESL::Domain* Mdomain, unsigned Pos, unsigned Line) : DomObject(Mdomain, Pos, Line) {};

int DIDESL::Module::run() {
	// domain->addFunctionsAll(functions);
	//for (Line& line : lines) {
		// line.run();
	//}
	return 0;
}

void DIDESL::Module::addFunction(int index) {
	//functions[-1];
}