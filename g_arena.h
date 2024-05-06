#ifndef G_ARENA_H
#define G_ARENA_H
#include <stdlib.h>
#include <string.h>
#include "g_vector.h"
#include <stdio.h>

typedef struct {
    g_vector_t arr;
    void * destructor;
} g_arena_t;

#define g_arena_init(arena, type) \
g_vector_init((arena).arr, type, 1); \
(arena).destructor = NULL;

#define g_arena_init_d(arena, type, deleter) \
g_vector_init((arena).arr, type, 1); \
(arena).destructor = deleter;\

#define g_arena_free(arena, type) \
if ((arena).destructor != NULL) g_vector_for_each((arena).arr, type, ((void (*)(type))(arena).destructor));\
g_vector_free(arena.arr);

#define __G_ARENA_DISAMBIGUATION(sign, type) \
\
static g_arena_t g_arena_init_##sign() {\
    g_arena_t newarena;\
    g_arena_init(newarena, type);\
    return newarena;\
}\
\
static g_arena_t g_arena_init_d_##sign(void * destructor) {\
    g_arena_t newarena;\
    g_arena_init_d(newarena, type, destructor);\
    return newarena;\
}\
\
static type * g_arena_new_ptr_##sign(g_arena_t * arena) {\
    g_vector_add(arena->arr, 0b0);\
    return &g_vector_get(arena->arr, type, arena->arr.len-1);\
}\
\
static size_t g_arena_new_index_##sign(g_arena_t * arena) {\
    g_vector_add(arena->arr, 0b0);\
    return arena->arr.len-1;\
}\
\
static void g_arena_free_##sign(g_arena_t * arena) {\
    g_arena_free((*arena), type);\
}\
static type * g_arena_get_##sign(g_arena_t arena, size_t id) {\
    return &g_vector_get(arena.arr, type, id);\
}

#define DECLARE_G_ARENA(type) __G_ARENA_DISAMBIGUATION(type, type)
#define DECLARE_G_ARENA_PTR(type) __G_ARENA_DISAMBIGUATION(type##_ptr, (type *))
#define DECLARE_G_ARENA_FUNC_PTR(typedef_n) __DECLARE_G_VECTOR_DISAMBIGUATION(typedef_n, typedef_n);

#endif