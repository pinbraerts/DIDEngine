#include "DIDESLLexer.h"
#ifndef DEBUGGING
#define DEBUGGING
#endif // !DEBUGGING
#include "../DEBUG.h"

void readScript(DIDESL::Lexer& lex) {
	DIDESL::Token tok = lex.next();
	while (tok.type != DIDESL::Token::END) {
		DEBUG_LOG(L'"', tok.value, L'"');
		tok = lex.next();
	}
}

bool test() {
	DEBUG_SEPARATOR = L"";
	DIDESL::Lexer lex;
#if 1
	lex.setString(
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
		L"}");
#else
	lex.setFile(L"DIDEngineScriptingLanguage/TestScript.dides");
#endif
	try {
		readScript(lex);
	}
	catch (DIDESL::Lexer::Error e) {
		DEBUG_LOG(e.toString());
	}
	return false;
}