#ifndef UTILS_H
#define UTILS_H

#define __ARGS_SELECTOR_8(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define __MACRO_BRACES(ARGS) __ARGS_SELECTOR_8 ARGS
#define __MACRO_SELECTOR(TARGET, ...) __MACRO_BRACES((__VA_ARGS__, TARGET##_8, TARGET##_7, TARGET##_6, TARGET##_5, TARGET##_4, TARGET##_3, TARGET##_2, TARGET##_1, ))
#define __CHOOSE_FROM_ARG(TARGET, ...) __MACRO_SELECTOR(TARGET, TARGET##_0 __VA_ARGS__ ())

template <size_t n> struct __counter {
	char __arr[n + 1];
};

template <size_t n> __counter<n> __counter_function(__counter<n>);

#define COUNTER_VALUE (sizeof(__counter_function(__counter<0>())) - 1)

#define COUNTER_INCREASE __counter<1> __counter_function(__counter<0>);

#endif // !UTILS_H