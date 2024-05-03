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
g_arena_t g_arena_init_##sign() {\
    g_arena_t newarena;\
    g_arena_init(newarena, type);\
    return newarena;\
}\
\
g_arena_t g_arena_init_d_##sign(void * destructor) {\
    g_arena_t newarena;\
    g_arena_init_d(newarena, type, destructor);\
    return newarena;\
}\
\
type * g_arena_new_ptr_##sign(g_arena_t * arena) {\
    g_vector_add(arena->arr, 0b0);\
    return &g_vector_get(arena->arr, type, arena->arr.len-1);\
}\
\
size_t g_arena_new_index_##sign(g_arena_t * arena) {\
    g_vector_add(arena->arr, 0b0);\
    return arena->arr.len-1;\
}\
\
void g_arena_free_##sign(g_arena_t * arena) {\
    g_arena_free((*arena), type);\
}\
type * g_arena_get_##sign(g_arena_t arena, size_t id) {\
    return &g_vector_get(arena.arr, type, id);\
}

#define DECLARE_G_ARENA(type) __G_ARENA_DISAMBIGUATION(type, type)
#define DECLARE_G_ARENA_PTR(type) __G_ARENA_DISAMBIGUATION(type##_ptr, (type *))

#endif