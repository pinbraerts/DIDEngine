#include "DIDEngineXMLLexer.h"

DIDEngineEnvironment::XMLLexer::XMLLexer(std::wstring path) : file(new std::wifstream(path)), currentLexem(DIDEngineEnvironment::XMLToken::START) {}

DIDEngineEnvironment::XMLToken DIDEngineEnvironment::XMLLexer::next() {
	if (file->eof()) return XMLToken(currentLexem = XMLToken::END, L"\n");
	switch (currentLexem) {
	case XMLToken::START: case XMLToken::RBRACE: {
		do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // ignore spaces, read next wchar_tacter
		if (file->eof()) return XMLToken(currentLexem = XMLToken::END, L"\n"); // end
		else if (currentCharacter == '<') { // LBRACE starts
			do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // ignore spaces, read next wchar_tacter
			if (currentCharacter == '/') return XMLToken(currentLexem = XMLToken::LBRACE, L"</"); // if '/' it's close LBRACE
			else if (currentCharacter == '?') { // format tag starts
				do
					if ((currentCharacter = file->get()) == '"') // ignore until '"'
						do
							currentCharacter = file->get();
						while (!file->eof() && currentCharacter != '"'); // if '"' ignore until next '"'
				while (!file->eof() && currentCharacter != '?'); // format must ends with "?"
				if ((currentCharacter = file->get()) != '>') break; // read end of format
				return next(); // return next DOM
			}
			else if (currentCharacter == '!') { // comment starts
				if ((currentCharacter = file->get()) != '-' && (currentCharacter = file->get()) != '-') break; // comment must starts with "!--"
				do {
					do
						currentCharacter = file->get();
					while (!file->eof() && currentCharacter != '-'); // ignore until "-"
					currentCharacter = file->get();
				} while (!file->eof() && currentCharacter != '-'); // comment must ends with "--"
				if ((currentCharacter = file->get()) != '>') break; // read end of comment
				return next(); // return next DOM
			}
			file->putback(currentCharacter); // if wchar_tacter isn't specific we have to put it back
			return XMLToken(currentLexem = XMLToken::LBRACE, L"<");
		}
		else if (currentLexem == XMLToken::RBRACE) { // after RBRACE may be TEXT
			std::wstring str = L"";
			do {
				str += currentCharacter;
				currentCharacter = file->get();
			} while (!file->eof() && currentCharacter != '<'); // read text
			file->putback(currentCharacter); // you should put '<' back
			return XMLToken(currentLexem = XMLToken::TEXT, str);
		}
		break;
	}
	case XMLToken::LBRACE: {
		do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
		if (file->eof()) break; // if eof after LBRACE it's error
		std::wstring str = L"";
		while (!file->eof() && isalpha(currentCharacter)) { // read identifier
			str += currentCharacter;
			currentCharacter = file->get();
		}
		if (file->eof() || str.size() == 0) break; // wrong identifier
		file->putback(currentCharacter); // you should putback non-identifier wchar_tacter
		return XMLToken(currentLexem = XMLToken::NAME, str);
	}
	case XMLToken::TEXT: {
		if (currentCharacter == '"') { // if '"' stay next should be NAME or RBRACE
			do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
			if (file->eof()) break; // after value mustn't be eof
			if (currentCharacter == '/') { // close RBRACE starts
				do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
				if (currentCharacter != '>') break; // next wchar_tacter should be '>'
				return XMLToken(currentLexem = XMLToken::RBRACE, L"/>");
			}
			if (currentCharacter == '>') return XMLToken(currentLexem = XMLToken::RBRACE, L">"); // it's RBRACE
			std::wstring str = L""; // NAME starts
			while (!file->eof() && isalpha(currentCharacter)) { // read identifier
				str += currentCharacter;
				currentCharacter = file->get();
			}
			if (file->eof() || str.size() == 0 || currentCharacter != '=') break; // after
			// you shouldn't put back '=' because next Token will use it
			return XMLToken(currentLexem = XMLToken::NAME, str);
		}
		do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
		if (file->eof()) break; // eof shouldn't be after TEXT
		if (currentCharacter == '<') { // LBRACE starts
			do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
			if (file->eof()) break; // eof musn't be after '<'
			if (currentCharacter == '/') return XMLToken(currentLexem = XMLToken::LBRACE, L"</"); // close LBRACE starts
			else if (currentCharacter == '?') { // format starts
				do
					if ((currentCharacter = file->get()) == '"')
						do
							currentCharacter = file->get();
						while (!file->eof() && currentCharacter != '"');
				while (!file->eof() && currentCharacter != '?');
				if ((currentCharacter = file->get()) != '>') break;
				return next();
			}
			else if (currentCharacter == '!') { // comment starts
				if ((currentCharacter = file->get()) != '-' && (currentCharacter = file->get()) != '-') break;
				do {
					do
						currentCharacter = file->get();
					while (!file->eof() && currentCharacter != '-');
					currentCharacter = file->get();
				} while (!file->eof() && currentCharacter != '-');
				return next();
			}
			file->putback(currentCharacter); // if it isn't special wchar_tacter you should put it back
			return XMLToken(currentLexem = XMLToken::LBRACE, L"<");
		}
		break;
	}
	case XMLToken::NAME: {
		if (currentCharacter == '=') { // TEXT value starts
			do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
			if (file->eof() || currentCharacter != '"') break; // after '=' should be '"'
			currentCharacter = file->get();
			std::wstring str = L"";
			while (!file->eof() && currentCharacter != '"') {
				str += currentCharacter;
				currentCharacter = file->get();
			}
			if (file->eof()) break;
			// you shouldn't put back '"' because next Token will use it
			return XMLToken(currentLexem = XMLToken::TEXT, str);
		}
		do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // wchar_tacter isn't special, read next wchar_tacter
		if (file->eof()) break; // eof can't be after NAME
		if (currentCharacter == '/') { // close RBRACE starts
			do currentCharacter = file->get(); while (!file->eof() && isspace(currentCharacter)); // read next wchar_tacter
			if (currentCharacter != '>') break; // close RBRACE must ends with '>'
			return XMLToken(currentLexem = XMLToken::RBRACE, L"/>");
		}
		if (currentCharacter == '>') return XMLToken(currentLexem = XMLToken::RBRACE, L">"); // it's RBRACE
		std::wstring str = L""; // identifier starts
		while (!file->eof() && isalpha(currentCharacter)) {
			str += currentCharacter;
			currentCharacter = file->get();
		}
		if (file->eof() || str.size() == 0 || currentCharacter != '=') break;
		return XMLToken(currentLexem = XMLToken::NAME, str);
	}
	}
	throw Error();
}

DIDEngineEnvironment::XMLLexer::~XMLLexer()
{
	delete file;
	delete &currentCharacter;
	delete &currentLexem;
}

/*
 TOK \ CURRTOK |	+START	|	+LBRACE	|	+RBRACE	|	+TEXT	|	+NAME	|
-----------------------------------------------------------------------------
	  =END	   |	  1		|	  0		|	  1		|	  0		|	  0		|
-----------------------------------------------------------------------------
	=LBRACE	   |	  1		|	  0		|	  1		|	  1		|	  0		|
-----------------------------------------------------------------------------
	=RBRACE    |	  0		|	  0		|	  0		|	  1		|	  1		|
-----------------------------------------------------------------------------
	 =TEXT     |	  0		|	  0		|	  1		|	  0		|	  1		|
-----------------------------------------------------------------------------
	 =NAME     |	  0		|	  1		|	  0		|	  1		|	  1		|
*/