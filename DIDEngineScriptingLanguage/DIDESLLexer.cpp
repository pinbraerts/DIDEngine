#include "DIDESLLexer.h"
#define DEBUGGING
#include "../DEBUG.h"

#define CASE(VALUE, OPER, ENTER) case VALUE: currentLexem = Token::##OPER; goto entered##ENTER;
#define CASE_OPERATOR_ENVIRONMENT(ENTER) \
CASE(L',', OPERATOR_ENVIRONMENT, ENTER)\
case L'.': {\
	if (getCharacter() == L'.')\
		if (getCharacter()) {\
			getCharacter();\
			return Token(currentLexem = Token::OPERATOR_ENVIRONMENT, L"...");\
		}\
		else throw Error();\
	else return Token(currentLexem = Token::OPERATOR_ENVIRONMENT, L".");\
}
#define CASE_ANNOTATION case L'@': return getAnnotation();
#define CASE_ENTERED(ENTER) \
default: break;\
entered##ENTER: return Token(currentLexem, getCharacterPost());
#define CASE_ARITHMETIC_SET case L'+': case L'-': case L'*': case L'/': {\
	DIDESLC_t lst = getCharacterPost();\
	if (!scriptStream.eof() && currentCharacter == L'=') {\
		getCharacter();\
		return Token(currentLexem = Token::OPERATOR_SET, (DIDESLS_t)L"" + lst + L'=');\
	}\
	return Token(currentLexem = Token::OPERATOR_ARITHMETIC, lst);\
}
#define CASE_BIT_BOOL \
case L'&': case L'|': {\
	DIDESLC_t lst = getCharacterPost();\
	if (currentCharacter == lst) return Token(currentLexem = Token::OPERATOR_BOOL, (DIDESLS_t)L"" + currentCharacter + getCharacterPost());\
	return Token(currentLexem = Token::OPERATOR_BIT, lst);\
}\
case L'^': case L'~': {\
	return Token(currentLexem = Token::OPERATOR_BIT, (DIDESLS_t)L"" + getCharacterPost());\
}
#define CASE_SET_BOOL case L'=': {\
	if (getCharacter() == L'=') return Token(currentLexem = Token::OPERATOR_BOOL, (DIDESLS_t)L"=" + getCharacterPost());\
	return Token(currentLexem = Token::OPERATOR_SET, L"=");\
}
#define CASE_BOOL_CMP case L'<': case L'>': case L'!': {\
	return Token(currentLexem = Token::OPERATOR_BOOL, (DIDESLS_t)L"" + getCharacterPost() + (currentCharacter == L'=' ? getCharacterPost() : L'\0'));\
}
#define CASE_BOOL_NO_SET case L'=': {\
	if (getCharacter() == L'=') return Token(currentLexem = Token::OPERATOR_BOOL, L"=" + getCharacterPost());\
	break;\
}

DIDESL::Lexer::Lexer() : currentLexem(Token::START) {}

DIDESL::Lexer::Lexer(DIDESLS_t Script) : currentLexem(DIDESL::Token::START), scriptStream(Script) {
	getCharacter();
}

void DIDESL::Lexer::setFile(DIDESLS_t Path) {
	std::wifstream file(Path);
	std::wostringstream wos;
	scriptStream.clear();
	DIDESLS_t str;
	while (std::getline(file, str)) wos << str << L'\n';
	scriptStream.str(wos.str());
	getCharacter();
}

DIDESL::DIDESLS_t DIDESL::Lexer::getWord() {
	DIDESLS_t str = L"";
	while (!scriptStream.eof() && (iswalpha(currentCharacter) || currentCharacter == L'_')) str += getCharacterPost();
	return str;
}

bool DIDESL::Lexer::isReservedFunctionWord(DIDESLS_t str) {
	return str == L"async" || str == L"function" || str == L"global";
}

bool DIDESL::Lexer::isType(DIDESLS_t str) {
	return str == L"Integer" || str == L"int" || str == L"String" ||
		str == L"string" || str == L"Listener" || str == L"Object" ||
		str == L"Event" || str == L"Bool" || str == L"bool" ||
		str == L"Resources"; // TODO: add types
}

bool DIDESL::Lexer::isReservedOperatorWord(DIDESLS_t str) {
	return str == L"if" || str == L"while" || str == L"return" ||
		str == L"throw Error()" || str == L"else"; // TODO: add words
}

bool DIDESL::Lexer::isBoolLiteral(DIDESLS_t str) {
	return str == L"true" || str == L"false";
}

DIDESL::Token DIDESL::Lexer::getAnnotation() { // TODO: turn to operations with stream
	getCharacter();
	ignoreSpaces();
	DIDESLS_t str = getWord();
	if (str.size()) return Token(currentLexem = Token::ANNOTATION, str);
	else throw Error();
}

DIDESL::DIDESLC_t DIDESL::Lexer::getCharacter()
{
	return currentCharacter = scriptStream.get();
}

DIDESL::DIDESLC_t DIDESL::Lexer::getCharacterPost()
{
	DIDESLC_t lst = currentCharacter;
	getCharacter();
	return lst;
}

bool DIDESL::Lexer::ignoreSpaces(bool isEnd) {
	while (!scriptStream.eof() && isspace(currentCharacter)) getCharacter();
	if (scriptStream.eof())
		if (isEnd) return true;
		else throw Error();
	else return false;
}

DIDESL::Token DIDESL::Lexer::getLiteral(bool isResF, bool isTypeR, bool errInEnd) {
	DIDESLS_t str = L"";
	if (currentCharacter == L'"' || currentCharacter == L'\'') {
		DIDESLC_t div = currentCharacter;
		getCharacter();
		while (!scriptStream.eof() && currentCharacter != div) {
			if (currentCharacter == L'\\') {
				getCharacter();
				if (scriptStream.eof()) throw Error();
				switch (currentCharacter) { // TODO: add more escapes
				case L'"': case L'\'': case L'\\': {
					str += currentCharacter;
					break;
				}
				case L'n': {
					str += L'\n';
					break;
				}
				case L't': {
					str += L'\t';
					break;
				}
				}
				continue;
			}
			str += getCharacterPost();
		}
		if (scriptStream.eof()) throw Error();
		getCharacter();
		return Token(currentLexem = Token::STRING_LITERAL, str);
	}
	else if(iswdigit(currentCharacter)) {
		DIDESLC_t fir = currentCharacter;
		if (!scriptStream.eof() && getCharacter() == L'x') {
			getCharacter();
			while (!scriptStream.eof() && (currentCharacter == L'0' || currentCharacter == L'1')) str += getCharacterPost();
		}
		else {
			scriptStream.putback(currentCharacter);
			currentCharacter = fir;
			while (!scriptStream.eof() && iswdigit(currentCharacter)) str += getCharacterPost();
		}
		if (!str.size()) throw Error();
		return Token(currentLexem = Token::NUMBER_LITERAL, str);
	}
	str = getWord();
	if (isBoolLiteral(str)) currentLexem = Token::BOOL_LITERAL;
	else if (isResF && isReservedFunctionWord(str)) currentLexem = Token::RES_FUNCTION;
	else if (isTypeR && isType(str)) currentLexem = Token::TYPE;
	else if (str.size()) currentLexem = Token::NAME;
	else if (errInEnd) throw Error();
	else return Token(Token::END, L"\n");
	return Token(currentLexem, str);
}

DIDESL::Token DIDESL::Lexer::next() {
	switch (currentLexem) {
	case Token::START: {
		if (ignoreSpaces(true)) return Token(Token::END, L"\n");
		if (currentCharacter == L'@') return getAnnotation();
		ignoreSpaces();
		DIDESLS_t str = getWord();
		if (isReservedFunctionWord(str)) currentLexem = Token::RES_FUNCTION;
		else throw Error();
		return Token(currentLexem, str);
	}
	case Token::TYPE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE_OPERATOR_ENVIRONMENT(11)
		CASE(L'(', OBRACE, 11)
		CASE(L')', CBRACE, 11)
		CASE_ANNOTATION
		CASE_ENTERED(11)
		}
		DIDESLS_t str = getWord();
		if (str.size()) return Token(currentLexem = Token::NAME, str);
		throw Error();
	}
	case Token::SEMICOLON: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE(L';', SEMICOLON, 0)
		CASE(L'(', OBRACE, 0)
		CASE(L'[', OSBRACE, 0)
		CASE(L'{', OCBRACE, 0)
		CASE(L'}', CCBRACE, 0)
		CASE(L'$', OPERATOR_REFERENCE, 0)
		CASE_ANNOTATION
		CASE_ENTERED(0)
		}
		DIDESLS_t str = getWord();
		if (isType(str)) currentLexem = Token::TYPE;
		else if (isReservedOperatorWord(str)) currentLexem = Token::RES_OPERATOR;
		else if (str.size()) currentLexem = Token::NAME;
		else throw Error();
		return Token(currentLexem, str);
	}
	case Token::NAME: case Token::CSBRACE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE_ARITHMETIC_SET
		CASE_BIT_BOOL
		CASE_SET_BOOL
		CASE_BOOL_CMP
		CASE_OPERATOR_ENVIRONMENT(1)
		CASE_ANNOTATION
		CASE(L'%', OPERATOR_ARITHMETIC, 1)
		CASE(L'(', OBRACE, 1)
		CASE(L')', CBRACE, 1)
		CASE(L'[', OSBRACE, 1)
		CASE(L']', CSBRACE, 1)
		CASE(L';', SEMICOLON, 1)
		CASE_ENTERED(1)
		}
		throw Error();
	}
	case Token::CBRACE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE_ARITHMETIC_SET
		CASE_BIT_BOOL
		CASE_SET_BOOL
		CASE(L'%', OPERATOR_ARITHMETIC, 2)
		CASE_BOOL_CMP
		CASE_OPERATOR_ENVIRONMENT(2)
		CASE(L'{', OCBRACE, 2)
		CASE(L'(', OBRACE, 2)
		CASE(L')', CBRACE, 2)
		CASE(L'[', OSBRACE, 2)
		CASE(L']', CSBRACE, 2)
		CASE_ANNOTATION
		CASE(L';', SEMICOLON, 2)
		CASE(L'$', OPERATOR_REFERENCE, 2)
		CASE_ENTERED(2)
		}
		return getLiteral();
	}
	case Token::STRING_LITERAL: case Token::NUMBER_LITERAL: case Token::BOOL_LITERAL: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE_ARITHMETIC_SET
		CASE_BIT_BOOL
		CASE_SET_BOOL
		CASE_BOOL_CMP
		CASE_OPERATOR_ENVIRONMENT(3)
		CASE_ANNOTATION
		CASE(L'%', OPERATOR_ARITHMETIC, 3)
		CASE(L')', CBRACE, 3)
		CASE(L']', CSBRACE, 3)
		CASE(L';', SEMICOLON, 3)
		CASE_ENTERED(3)
		}
		throw Error();
	}
	case Token::RES_FUNCTION: {
		ignoreSpaces();
		if (currentCharacter == L'(' || currentCharacter == L'{') return Token(currentLexem = currentCharacter == L'(' ? Token::OBRACE : Token::OCBRACE, (DIDESLS_t)L"" + getCharacterPost());
		else if (currentCharacter == L'@') return getAnnotation();
		DIDESLS_t str = getWord();
		if (isReservedFunctionWord(str)) return Token(currentLexem = Token::RES_FUNCTION, str);
		else if (str.size()) return Token(currentLexem = Token::NAME, str);
		throw Error();
	}
	case Token::RES_OPERATOR: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE_ARITHMETIC_SET
		CASE_BIT_BOOL
		CASE_SET_BOOL
		CASE_BOOL_CMP
		CASE_OPERATOR_ENVIRONMENT(4)
		CASE_ANNOTATION
		CASE(L'(', OBRACE, 4)
		CASE(L'{', OCBRACE, 4)
		CASE(L';', SEMICOLON, 4)
		CASE(L'$', OPERATOR_REFERENCE, 4)
		CASE_ENTERED(4)
		}
		return getLiteral();
	}
	case Token::OPERATOR_ARITHMETIC: case Token::OPERATOR_BIT: case Token::OSBRACE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE(L'+', OPERATOR_ARITHMETIC, 5)
		CASE(L'-', OPERATOR_ARITHMETIC, 5)
		CASE(L'*', OPERATOR_ARITHMETIC, 5)
		CASE(L'%', OPERATOR_ARITHMETIC, 5)
		CASE(L'/', OPERATOR_ARITHMETIC, 5)
		CASE(L'(', OBRACE, 5)
		CASE(L';', SEMICOLON, 5)
		CASE(L'$', OPERATOR_REFERENCE, 5)
		CASE_BOOL_NO_SET
		CASE_BIT_BOOL
		CASE_BOOL_CMP
		CASE_ANNOTATION
		CASE_ENTERED(5)
		}
		return getLiteral();
	}
	case Token::OPERATOR_SET: case Token::OPERATOR_BOOL: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE(L'+', OPERATOR_ARITHMETIC, 6)
		CASE(L'-', OPERATOR_ARITHMETIC, 6)
		CASE(L'*', OPERATOR_ARITHMETIC, 6)
		CASE(L'/', OPERATOR_ARITHMETIC, 6)
		CASE(L'%', OPERATOR_ARITHMETIC, 6)
		CASE(L'(', OBRACE, 6)
		CASE(L';', SEMICOLON, 6)
		CASE(L'$', OPERATOR_REFERENCE, 6)
		CASE_BIT_BOOL
		CASE_BOOL_NO_SET
		CASE_BOOL_CMP
		CASE_ANNOTATION
		CASE_ENTERED(6)
		}
		return getLiteral(currentLexem == Token::OPERATOR_SET, true);
	}
	case Token::OPERATOR_ENVIRONMENT: case Token::OBRACE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE(L'+', OPERATOR_ARITHMETIC, 7)
		CASE(L'-', OPERATOR_ARITHMETIC, 7)
		CASE(L'*', OPERATOR_ARITHMETIC, 7)
		CASE(L'/', OPERATOR_ARITHMETIC, 7)
		CASE(L'%', OPERATOR_ARITHMETIC, 7)
		CASE(L'(', OBRACE, 7)
		CASE(L')', CBRACE, 7)
		CASE(L';', SEMICOLON, 7)
		CASE_BOOL_NO_SET
		CASE_BIT_BOOL
		CASE_BOOL_CMP
		CASE_OPERATOR_ENVIRONMENT(7)
		CASE_ANNOTATION
		CASE_ENTERED(7)
		}
		return getLiteral(true, true);
	}
	case Token::CCBRACE: {
		if (ignoreSpaces(true)) return Token(currentLexem = Token::END, L"\n");
		switch (currentCharacter) {
		CASE(L'}', CCBRACE, 8)
		CASE_ANNOTATION
		CASE(L';', SEMICOLON, 8)
		CASE(L'$', OPERATOR_REFERENCE, 8)
		CASE_ENTERED(8)
		}
		DIDESLS_t str = getWord();
		if (isType(str)) currentLexem = Token::TYPE;
		else if (isReservedFunctionWord(str)) currentLexem = Token::RES_FUNCTION;
		else if (isReservedOperatorWord(str)) currentLexem = Token::RES_OPERATOR;
		else if (str.size()) currentLexem = Token::NAME;
		else throw Error();
		return Token(currentLexem, str);
	}
	case Token::OCBRACE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE(L'{', OCBRACE,9)
		CASE_ANNOTATION
		CASE(L';', SEMICOLON, 9)
		CASE(L'$', OPERATOR_REFERENCE, 9)
		CASE_ENTERED(9)
		}
		DIDESLS_t str = getWord();
		if (isType(str)) currentLexem = Token::TYPE;
		else if (isReservedOperatorWord(str)) currentLexem = Token::RES_OPERATOR;
		else if (str.size()) currentLexem = Token::NAME;
		else throw Error();
		return Token(currentLexem, str);
	}
	case Token::ANNOTATION: {
		ignoreSpaces();
		return getLiteral(false, true);
	}
	case Token::OPERATOR_REFERENCE: {
		ignoreSpaces();
		switch (currentCharacter) {
		CASE(L'(', OBRACE, 10)
		CASE(L'$', OPERATOR_REFERENCE, 10)
		CASE_ENTERED(10)
		}
		DIDESLS_t str = getWord();
		if (isType(str)) currentLexem = Token::TYPE;
		else if (str.size()) currentLexem = Token::NAME;
		else throw Error();
		return Token(currentLexem, str);
	}
	}
	throw Error();
}