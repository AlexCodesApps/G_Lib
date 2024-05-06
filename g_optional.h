#ifndef G_OPTIONAL_H
#define G_OPTIONAL_H
#include <stdbool.h>
#define DECLARE_G_OPTIONAL(type) \
typedef struct {\
    type value = (type)0;\
    bool valid;\
} g_optional_##type;

typedef struct {
    void * value;
    bool valid;
} g_optional_generic_t;

#define DECODE_PTR(ptr, type) (*(type*)ptr)

#define g_optional_is_valid(optional) (optional.valid)

#define g_optional_unwrap(optional) (optional.value)

#define g_optional_unwrap_generic(optional, type) DECODE_PTR(optional.value, type)

#endif