#ifndef DID_ENGINE_SCRIPTING_LANGUAGE_DEFINITIONS_H
#define DID_ENGINE_SCRIPTING_LANGUAGE_DEFINITIONS_H

#include <string>
#include <vector>
#include <map>

namespace DIDESL {
	struct Token;
	struct DomObject;
	struct Argument;
	struct Domain;
	class Lexer;
	class Parcer;
	class Module;
	class Function;
	class Line;
	typedef std::wstring DIDESLS_t; // string
	typedef wchar_t DIDESLC_t; // char
	template<class Elem> using DIDESLV_t = std::vector<Elem>;
	template<class Key, class Elem> using DIDESLM_t = std::map<Key, Elem>;
	typedef long unsigned DIDESLA_t;
	typedef unsigned DIDESLBM_t;
	class Root;

	enum Type { // TODO: add types
		Root,
		Integer,
		String,
		int_t,
		string_t
	};
}

struct DIDESL::DomObject {
	Domain *domain;
	const unsigned pos;
	const unsigned line;

	virtual int run(); // int -- result

	DomObject(Domain* Mdomain, unsigned Pos, unsigned Line) : domain(Mdomain), pos(Pos), line(Line) {};
};

#endif // !DID_ENGINE_SCRIPTING_LANGUAGE_DEFINITIONS_H
