#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_DEFINITIONS_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_DEFINITIONS_H

#include <string>
#include <vector>

namespace DIDESL {
	struct Token;
	struct Argument;
	class Lexer;
	class Parcer;
	class Domain;
	class Function;
	class Line;
	typedef short DIDESLBM_t; // bit mask
	typedef std::wstring DIDESLS_t; // string
	typedef wchar_t DIDESLC_t; // char
	template<class Elem> using DIDESLV_t = std::vector<Elem>;
	typedef unsigned DIDESLA_t;

	enum Type { // TODO: add types
		Root,
		Integer,
		String,
		int_t,
		string_t
	};
}

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_DEFINITIONS_H
