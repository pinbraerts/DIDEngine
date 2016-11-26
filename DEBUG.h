#ifndef DEBUG_H

#define DEBUG_H

#ifdef DEBUGGING

#include <iostream>
#include <string>

#define DEBUG_LOG(...) __DEBUG_H_DEBUG_LOG(__VA_ARGS__)

#ifndef STANDART_DEBUG_PREFIX
#define STANDART_DEBUG_PREFIX L"DEBUG: "
#endif // !STANDART_DEBUG_PREFIX

#ifndef STANDART_DEBUG_SEPARATOR
#define STANDART_DEBUG_SEPARATOR L", "
#endif // !STANDART_DEBUG_SEPARATOR

#ifndef STANDART_DEBUG_ENDLINE
#define STANDART_DEBUG_ENDLINE L"\n"
#endif // !STANDART_DEBUG_ENDLINE

#ifndef STANDART_DEBUG_SUFFIX
#define STANDART_DEBUG_SUFFIX L""
#endif // !STANDART_DEBUG_SUFFIX


static std::wstring DEBUG_SUFFIX = STANDART_DEBUG_SUFFIX;
static std::wstring DEBUG_PREFIX = STANDART_DEBUG_PREFIX;
static std::wstring DEBUG_SEPARATOR = STANDART_DEBUG_SEPARATOR;
static std::wstring DEBUG_ENDLINE = STANDART_DEBUG_ENDLINE;

template<typename T, typename ...RT> void __DEBUG_H_DEBUG_LOG(const T arg, const RT& ...args) {
	std::wcout << DEBUG_PREFIX << arg << DEBUG_SEPARATOR;
	__DEBUG_H_DEBUG_LOG_SECONDLY(args...);
}

template<typename T = const DIDESLC_t*> void __DEBUG_H_DEBUG_LOG(const T arg = "") {
	std::wcout << DEBUG_PREFIX << arg << DEBUG_SUFFIX << DEBUG_ENDLINE;
}

template<typename T, typename ...RT> void __DEBUG_H_DEBUG_LOG_SECONDLY(const T arg, const RT& ...args) {
	std::wcout << arg << DEBUG_SEPARATOR;
	__DEBUG_H_DEBUG_LOG_SECONDLY(args...);
}

template<typename T> void __DEBUG_H_DEBUG_LOG_SECONDLY(const T arg) {
	std::wcout << arg << DEBUG_SUFFIX << DEBUG_ENDLINE;
}

#else

#define DEBUG_LOG(...)

#endif // DEBUGGING
#endif // !DEBUG_H
