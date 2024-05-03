#ifndef G_VECTOR_H
#define G_VECTOR_H
#include <stdlib.h>
#include <string.h>

typedef struct g_vector {
    size_t size;
    size_t len;
    size_t element_size;
    void* arr;
} g_vector_t;

#define g_vector_init(vec, Type, Len) \
(vec).len = 0;\
(vec).element_size = sizeof(Type);\
(vec).size = (Len > 1) ? Len * (vec).element_size : 2 * (vec).element_size;\
if (Len > 0) {\
    (vec).arr =  malloc((vec).size);\
}\
else (vec).arr = NULL;\

#define g_vector_get(vec, type, index) ((type*)(vec).arr)[index]

#define g_vector_add(vec, element) \
if ((vec).len * (vec).element_size >= (vec).size) {\
(vec).size *= 2;\
(vec).arr = realloc((vec).arr, (vec).size);\
}\
((typeof(element)*)(vec).arr)[(vec).len++] = element;

#define g_vector_free(vec) \
if ((vec).arr != NULL) free((vec).arr); \
(vec).size = 0; \
(vec).len = 0; \
(vec).element_size = 0;

#define g_vector_remove(vec, index) \
if (index < vec.len && vec.len >= 0 && vec.len > 0) {\
    if (index == vec.len -1) vec.len--;\
    else memcpy(&vec.arr[index*vec.element_size], &vec.arr[(index+1)*vec.element_size], (--vec.len - index)*vec.element_size);\
}\

#define g_vector_transform(vec, type, func) \
for (int i = 0; i < vec.len; i++) {\
    g_vector_get(vec, type, i) = func(g_vector_get(vec, type, i));\
}

#define g_vector_for_each(vec, type, func) \
for (int i = 0; i < vec.len; i++) {\
    func(g_vector_get(vec, type, i));\
}

#define g_vector_get_back(vec, type) g_vector_get(vec, type, vec.len-1)
#define g_vector_get_front(vec, type) g_vector_get(vec, type, 0)
#define g_vector_pop_back(vec, type) g_vector_remove(vec, vec.len-1);
#define g_vector_pop_front(vec, type) g_vector_remove(vec, 0);

#define __DECLARE_G_VECTOR_DISAMBIGUATION(sign, type) \
\
g_vector_t g_vector_init_##sign(int len) {\
    g_vector_t newvec;\
    g_vector_init(newvec, type, len);\
    return newvec;\
}\
\
type g_vector_get_##sign(g_vector_t vec, int index) {\
    return g_vector_get(vec, type, index);\
}\
\
void g_vector_transform_##sign(g_vector_t vec, type(*func)(type operand)) {\
    g_vector_transform(vec, type, func);\
}\
\
void g_vector_for_each_##sign(g_vector_t vec, void(*func)(type operand)) {\
    g_vector_for_each(vec, type, func);\
}\
\
type g_vector_add_##sign(g_vector_t * vec, type element) {\
    g_vector_add(*vec, element);\
    return g_vector_get(*vec, type, vec->len);\
}

#define DECLARE_G_VECTOR(type) __DECLARE_G_VECTOR_DISAMBIGUATION(type, type)

#define DECLARE_G_VECTOR_PTR(type) __DECLARE_G_VECTOR_DISAMBIGUATION(type##_ptr, type*)

#define DECLARE_G_VECTOR_FUNC_PTR(typedef_n) __DECLARE_G_VECTOR_DISAMBIGUATION(typedef_n, typedef_n)

void g_vector_free_ptr(g_vector_t target) {
    g_vector_for_each(target, void*, free);
    g_vector_free(target);
}

g_vector_t g_vector_copy(const g_vector_t target) {
    g_vector_t val = {.size = target.size, .len = target.len, .element_size = target.element_size};
    val.arr = malloc(val.size);
    memcpy(val.arr, target.arr, val.size);
    return val;
}

void g_vector_resize(g_vector_t target, unsigned int len) {
if (target.len > len) target.len = len;
target.size = len * target.element_size;
target.arr = realloc(target.arr, target.size);
}

#endif