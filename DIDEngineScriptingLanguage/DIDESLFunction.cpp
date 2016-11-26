#include "DIDESLFunction.h"

DIDESL::Function::Function(DIDESLS_t Name, std::vector<Line*> Lines, std::vector<Argument> Args, DIDESLBM_t Words, Domain* Parent) : name(Name), lines(Lines), args(Args), words(Words), parent(Parent) {}

DIDESL::DIDESLA_t DIDESL::Function::call(std::vector<Argument> args) { // TODO: add lines
	return DIDESLA_t();
}
