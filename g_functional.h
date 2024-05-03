#ifndef G_FUNCTIONAL_H
#define G_FUNCTIONAL_H
#define VOID_FUNCTION_TYPE(type) typedef void(*void_function_##type)(type);
#define TYPE_FUNCTION_VOID(type) typedef void(*type##_function_void)(type);
typedef void (*VOID_FUNCTION_VOID)(void);
#endif
