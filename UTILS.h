#ifndef UTILS_H
#define UTILS_H

#define __MACRO_BRACES(TARGET, ARGS) TARGET ARGS
#if 0
#define __ARGS_SELECTOR_0(X, ...) X
#define __ARGS_SELECTOR_1(_1, X, ...) X
#define __CONCAT(X, Y) X##Y
#define __BRCONCAT(X, Y) __MACRO_BRACES(__CONCAT, (X, Y))
#define __FILL() ,0
#define __MACRO_LOOP(TARGET, ...) __MACRO_BRACES(__BRCONCAT(TARGET,\
	__MACRO_BRACES(__ARGS_SELECTOR_1,\
	(__FILL __MACRO_BRACES(__ARGS_SELECTOR_0, (__VA_ARGS__)) (), 1))), (__VA_ARGS__))
#define __COUNT_LOOP_1(X, ...) __BRCONCAT(1, __MACRO_BRACES(__MACRO_LOOP, (__COUNT_LOOP_, __VA_ARGS__)))
#define __COUNT_LOOP_0()
#define __CHOOSE_FROM_ARG_NEW(TARGET, ...) __BRCONCAT(TARGET, __MACRO_BRACES(__MACRO_LOOP, (__COUNT_LOOP_, __VA_ARGS__)))(__VA_ARGS__)
#endif
#define __ARGS_SELECTOR_8(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define __MACRO_SELECTOR(TARGET, ...) __MACRO_BRACES(__ARGS_SELECTOR_8, (__VA_ARGS__, TARGET##_8, TARGET##_7, TARGET##_6, TARGET##_5, TARGET##_4, TARGET##_3, TARGET##_2, TARGET##_1, ))
#define __CHOOSE_FROM_ARG(TARGET, ...) __MACRO_SELECTOR(TARGET, TARGET##_0 __VA_ARGS__ ())

// template<class RET, class ...ARGS> using Function = RET(*)(ARGS...); -- ���, ���������� ���-��� ���������, ��������

#endif // !UTILS_H