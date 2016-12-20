#include "DIDESLLexer.h"
#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING
#include "../DEBUG.h"

DIDESL::Lexer::Lexer() {}

DIDESL::Lexer::Lexer(DIDESLS_t Script) : script(Script), lines(1), pos(0) {
	getCharacter();
}

void DIDESL::Lexer::setFile(DIDESLS_t Path) {
	lines = 1;
	pos = 0;
	std::wifstream file(Path);
	if (!file) throw EOFError();
	std::wostringstream wos;
	script.clear();
	DIDESLS_t str;
	while (std::getline(file, str)) wos << str << L'\n';
	script.str(wos.str());
	getCharacter();
}

void DIDESL::Lexer::setString(DIDESLS_t Script) {
	lines = 1;
	pos = 0;
	script.str(Script);
	script.seekg(0);
	getCharacter();
}

void DIDESL::Lexer::setStream(std::wistringstream newStream) {
	lines = 1;
	pos = 0;
	script.str(newStream.str());
	script.seekg(0);
	getCharacter();
}

unsigned DIDESL::Lexer::getPos() {
	return pos;
}

unsigned DIDESL::Lexer::getLines() {
	return lines;
}

/// <summary>Starts read word from current character</summary>
DIDESL::DIDESLS_t DIDESL::Lexer::getWord() {
	DIDESLS_t str = L"";
	while (!script.eof() && (iswalpha(currentCharacter) || currentCharacter == L'_')) str += getCharacterPost();
	return str;
}

bool DIDESL::Lexer::isReservedFunctionWord(DIDESLS_t str) {
	return str == L"async" || str == L"function" || str == L"global"; // TODO: add words
}

bool DIDESL::Lexer::isType(DIDESLS_t str) {
	return str == L"Integer" || str == L"int" || str == L"String" ||
		str == L"string" || str == L"Listener" || str == L"Object" ||
		str == L"Event" || str == L"Bool" || str == L"bool" ||
		str == L"Resources"; // TODO: add types
}

bool DIDESL::Lexer::isReservedOperatorWord(DIDESLS_t str) {
	return str == L"if" || str == L"while" || str == L"return" ||
		str == L"break" || str == L"else"; // TODO: add words
}

bool DIDESL::Lexer::isBoolLiteral(DIDESLS_t str) {
	return str == L"true" || str == L"false";
}

bool DIDESL::Lexer::isBinAlpha(DIDESLC_t c) {
	return c == L'0' || c == L'1';
}

bool DIDESL::Lexer::isOctalAlpha(DIDESLC_t c) {
	return isBinAlpha(c) || c == L'2' || c == L'3' || c == L'4' || c == L'5' || c == L'6' || c == L'7';
}

bool DIDESL::Lexer::isHexAlpha(DIDESLC_t c) {
	return iswdigit(c) || c == L'a' || c == L'b' || c == 'c' || c == L'd' || c == L'e' || c == L'f' || c == L'A' || c == L'B' || c == 'C' || c == L'D' || c == L'E' || c == L'F';
}

/// <summary>Gets and returns next character</summary>
DIDESL::DIDESLC_t DIDESL::Lexer::getCharacter()
{
	if (script.eof()) return L'\n';
	else if (currentCharacter == L'\n') {
		++lines;
		pos = 1;
	}
	else ++pos;
	return currentCharacter = script.get();
}

/// <summary>Gets next character but returns current character</summary>
DIDESL::DIDESLC_t DIDESL::Lexer::getCharacterPost()
{
 	DIDESLC_t lst = currentCharacter;
	getCharacter();
	return lst;
}

#define SIMPLE_CASE(X, TYPE) case X: return Token(Token:: TYPE, getCharacterPost())
#define IF_TWO_CASE(X, NEXT, IFX, IFNEXT)\
case X:\
	if(getCharacter() == NEXT) return Token(Token:: IFNEXT, (DIDESLS_t)L"" + X + getCharacterPost());\
	else return Token(Token::IFX, X)
#define NUMBER_LITERAL_CASE(X, TYPE, FUNC)\
			X\
				while (!script.eof() && FUNC (getCharacter()))\
					str += currentCharacter;\
				if (str.empty()) throw EOFError();\
				return Token(Token:: NUMBER_LITERAL##TYPE, str)

/// <summary>Returns next token</summary>
DIDESL::Token DIDESL::Lexer::next() {
	while (!script.eof() && isspace(currentCharacter)) getCharacter();
	if (script.eof()) return Token(Token::END, L'\n');
	switch (currentCharacter) {
	SIMPLE_CASE(L'(', OBRACE);
	SIMPLE_CASE(L')', CBRACE);
	SIMPLE_CASE(L'{', OCBRACE);
	SIMPLE_CASE(L'}', CCBRACE);
	SIMPLE_CASE(L'[', OSBRACE);
	SIMPLE_CASE(L']', CSBRACE);
	SIMPLE_CASE(L'^', OPERATOR_BIT);
	SIMPLE_CASE(L'~', OPERATOR_BIT);
	SIMPLE_CASE(L';', SEMICOLON);
	SIMPLE_CASE(L',', OPERATOR_ENVIRONMENT);
	IF_TWO_CASE(L'!', L'=', OPERATOR_BOOL, OPERATOR_BOOL);
	IF_TWO_CASE(L'>', L'=', OPERATOR_BOOL, OPERATOR_BOOL);
	IF_TWO_CASE(L'<', L'=', OPERATOR_BOOL, OPERATOR_BOOL);
	IF_TWO_CASE(L'=', L'=', OPERATOR_SET, OPERATOR_BOOL);
	IF_TWO_CASE(L'&', L'&', OPERATOR_BIT, OPERATOR_BOOL);
	IF_TWO_CASE(L'|', L'|', OPERATOR_BIT, OPERATOR_BOOL);
	IF_TWO_CASE(L'+', L'=', OPERATOR_ARITHMETIC, OPERATOR_SET);
	IF_TWO_CASE(L'-', L'=', OPERATOR_ARITHMETIC, OPERATOR_SET);
	IF_TWO_CASE(L'*', L'=', OPERATOR_ARITHMETIC, OPERATOR_SET);
	IF_TWO_CASE(L'/', L'=', OPERATOR_ARITHMETIC, OPERATOR_SET);
	IF_TWO_CASE(L'%', L'=', OPERATOR_ARITHMETIC, OPERATOR_SET);
	case L'.':
		if (!script.eof() && getCharacter() == L'.' && script.peek() == L'.') {
				getCharacter();
				getCharacter();
				return Token(Token::OPERATOR_ENVIRONMENT, L"...");
		}
		else return Token(Token::OPERATOR_ENVIRONMENT, L'.');
	case L'"': case L'\'': {
		DIDESLC_t div = currentCharacter;
		DIDESLS_t str = L"";
		while (!script.eof() && getCharacter() != div) {
			if (currentCharacter == L'\\') {
				getCharacter();
				if (script.eof()) throw EOFError();
				switch (currentCharacter) { // TODO: add more escapes
				case L'"': case L'\'': case L'\\':
					str += currentCharacter;
					break;
				case L'n':
					str += L'\n';
					break;
				case L't':
					str += L'\t';
					break;
				}
				continue;
			}
			str += currentCharacter;
		}
		if (currentCharacter != div) throw EOFError();
		getCharacter();
		return Token(Token::STRING_LITERAL, str);
	}
	case L'@': {
		getCharacter();
		return Token(Token::ANNOTATION, getWord());
	}
	default: {
		DIDESLS_t str = L"";
		if (iswdigit(currentCharacter)) {
			if (script.eof()) return Token(Token::NUMBER_LITERAL, getCharacterPost());
			switch (script.peek()) {
			NUMBER_LITERAL_CASE(case L'b': getCharacter(); getCharacter();, _BINARY, isBinAlpha);
			NUMBER_LITERAL_CASE(case L'o': getCharacter(); getCharacter();, _OCTAL, isOctalAlpha);
			NUMBER_LITERAL_CASE(case L'x': getCharacter(); getCharacter();, _MHEX, isHexAlpha);
			NUMBER_LITERAL_CASE(default:, , iswdigit);
			}
		}
		str = getWord();
		if (str.empty()) throw EOFError();
		Token::Lexem tem = isReservedFunctionWord(str) ? Token::RES_FUNCTION :
			isReservedOperatorWord(str) ? Token::RES_OPERATOR :
			isType(str) ? Token::TYPE :
			Token::NAME;
		return Token(tem, str);
	}
	}
}
