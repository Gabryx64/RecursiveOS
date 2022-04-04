#ifndef LIBK_MAP_MACRO_H
#define LIBK_MAP_MACRO_H 1

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...)  EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define MAP_MACRO_END(...)
#define MAP_MACRO_OUT
#define MAP_MACRO_COMMA ,

#define MAP_MACRO_GET_END2() 0, MAP_MACRO_END
#define MAP_MACRO_GET_END1(...) MAP_MACRO_GET_END2
#define MAP_MACRO_GET_END(...) MAP_MACRO_GET_END1
#define MAP_MACRO_NEXT0(test, next, ...) next MAP_MACRO_OUT
#define MAP_MACRO_NEXT1(test, next) MAP_MACRO_NEXT0(test, next, 0)
#define MAP_MACRO_NEXT(test, next)  MAP_MACRO_NEXT1(MAP_MACRO_GET_END test, next)

#define MAP_MACRO0(f, x, peek, ...) f(x) MAP_MACRO_NEXT(peek, MAP_MACRO1)(f, peek, __VA_ARGS__)
#define MAP_MACRO1(f, x, peek, ...) f(x) MAP_MACRO_NEXT(peek, MAP_MACRO0)(f, peek, __VA_ARGS__)

#define MAP_MACRO_LIST_NEXT1(test, next) MAP_MACRO_NEXT0(test, MAP_MACRO_COMMA next, 0)
#define MAP_MACRO_LIST_NEXT(test, next)  MAP_MACRO_LIST_NEXT1(MAP_MACRO_GET_END test, next)

#define MAP_MACRO_LIST0(f, x, peek, ...) f(x) MAP_MACRO_LIST_NEXT(peek, MAP_MACRO_LIST1)(f, peek, __VA_ARGS__)
#define MAP_MACRO_LIST1(f, x, peek, ...) f(x) MAP_MACRO_LIST_NEXT(peek, MAP_MACRO_LIST0)(f, peek, __VA_ARGS__)

#define MAP_MACRO(f, ...) EVAL(MAP_MACRO1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define MAP_MACRO_LIST(f, ...) EVAL(MAP_MACRO_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#endif
