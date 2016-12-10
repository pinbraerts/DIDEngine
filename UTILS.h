#ifndef UTILS_H
#define UTILS_H

#define __ARGS_SELECTOR_8(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define __MACRO_BRACES(TARGET, ARGS) TARGET ARGS
#define __MACRO_SELECTOR(TARGET, ...) __MACRO_BRACES(__ARGS_SELECTOR_8, (__VA_ARGS__, TARGET##_8, TARGET##_7, TARGET##_6, TARGET##_5, TARGET##_4, TARGET##_3, TARGET##_2, TARGET##_1, ))
#define __CHOOSE_FROM_ARG(TARGET, ...) __MACRO_SELECTOR(TARGET, TARGET##_0 __VA_ARGS__ ())

// template<class RET, class ...ARGS> using Function = RET(*)(ARGS...); -- так, захотелось кое-что проверить, работает

#endif // !UTILS_H