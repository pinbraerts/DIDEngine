
#if 1
#define DEBUGGING

#include "DEBUG.h"
#include "DIDEngine.h"
#include "DIDEngineScriptingLanguage\DIDESL.h"
int main() {
	{
	/*
	L"async function onGameStart(Object sender, ...args) {\n"
	L"	Resources res = getResources();\n"
	L"	Object mPlayer = sender.getChild(res.objects.player);\n"
	L"	Event mPlayerKick = mPlayer.getEvent(\"Kick\");\n"
	L"	Object mEnemy = sender.getChild(res.objects.enemy);\n"
	L"	Event mPlayerKick = mEnemy.getEvent(\"Kick\");\n"
	L"	while(true) {\n"
	L"		if(input(\"Kick enemy ? (y/n) \") == \"y\") {\n"
	L"			mPlayerKick.call(mPlayer, mEnemy.getId());\n"
	L"		}\n"
	L"		mEnemyKick.call(mEnemy, mPlayer.getId());\n"
	L"	}\n"
	L"}\n"
	L"async function onDead(Object sender, ...args) {\n"
	L"	log(sender.name + \" win, \" + getGameObject().getObject(args.popId()).name + \" lose!\");\n"
	L"	getGameObject().getEvent(res.events.exit).call(sender);\n"
	L"}\n"
	L"async function onKick(Object sender, ...args) {\n"
	L"	Resources res = getResources();\n"
	L"	Object target = getGameObject().getObject(args.popId());\n"
	L"	int value = res.getInteger(res.integers.strength_koeff) * sender.getProperty(\"Strength\");\n"
	L"	log(sender.name + \" kick \" + target.name + \" on \" + value + \" points!\");\n"
	L"	target.incProperty(\"Health\", -value);\n"
	L"}"
	*/
	}
	DIDESL::Lexer lex;
	lex.setFile(L"C:/Users/Dima.WIN-V4RR52DS4SJ/Documents/DIDEG/DIDESLExample.dides");
	DEBUG_SEPARATOR = L"";
	DIDESL::Token tok = lex.next();
	while (tok.type != DIDESL::Token::END) {
		DEBUG_LOG(L'"', tok.value, L'"');
		tok = lex.next();
	}
	while (true);
	return 0;
}
#else
extern "C" {
#include <stdio.h>

	int dlinastroki(const char s[]) {
		int i = 0;
		while (s[i] != '\0') {
			i++;
		}
		return i;
	}

	int sravneniestrok(const char s1[], const char s2[]) {
		int i = 0;
		while (s1[i] == s2[i] && s1[i] != '\0') i++;
		if (s1[i] > s2[i] || (s1[i] != '\0' && s2[i] == '\0')) i = 1;
		else if (s2[i] > s1[i] || (s2[i] != '\0' && s1[i] == '\0')) i = -1;
		else i = 0;
		return i;
	}

	int main(void) {
		char c[48];
		printf_s("Input a line, please: ");
		scanf_s("%s", c);
		printf_s("Length of the line = %d\n", dlinastroki(c));
		if (dlinastroki("a") != 1) printf_s("Error1!!!\n");
		if (dlinastroki("") != 0) printf_s("Error0!!!\n");
		if (dlinastroki("zthtzh") != 6) printf_s("Error6!!!\n");
		char s1[48];
		printf_s("Input a \"first\" line, please: ");
		scanf_s("%s", s1);
		char s2[48];
		printf_s("Input a \"second\" line, please: ");
		scanf_s("%s", s2);
		printf_s("Result: %d\n", sravneniestrok(s1, s2));
		if (sravneniestrok("a", "a") != 0) printf_s("ErrorEqual!!!\n");
		if (sravneniestrok("abc", "az") != -1) printf_s("ErrorLess!!!\n");
		if (sravneniestrok("ab", "aa") != 1) printf_s("ErrorMore!!!\n");
	}
}
#endif