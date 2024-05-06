#ifndef G_STRING_H
#define G_STRING_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "g_vector.h"

typedef struct {
    char * data;
    size_t len;
} g_string_t;

DECLARE_G_VECTOR(g_string_t)

g_vector g_string_pool_init() {
    g_vector n_pool = g_vector_init_g_string_t(1);
    return n_pool;
}

g_string_t g_string_pool_new(g_vector * pool, const char * data) {
    g_string_t str;
    str.data = (char*)malloc(sizeof(char) * strlen(data));
    str.len = strlen(data);
    g_vector_add_g_string_t(pool, str);
    return str;
}

g_string_t g_string_pool_new_empty(g_vector * pool, size_t len) {
    g_string_t str;
    str.len = len;
    str.data = (char*)malloc(sizeof(char) * len);
    g_vector_add_g_string_t(pool, str);
    return str;
}

void g_string_insert(g_string_t str, const char * data, int index) {
    memcpy(str.data+index*sizeof(char), data, strlen(data)*sizeof(char));
}

void g_string_overwrite(g_string_t str, const char * data, int index) {
    g_string_insert(str, data, index);
    str.data[strlen(data)] = '\0';
}

g_string_t g_string_free(g_string_t str) {
    free(str.data);
    str.len = 0;
    return str;
}

void g_string_pool_free(g_vector_t pool) {
    g_vector_transform_g_string_t(pool, g_string_free);
    g_vector_free(pool);
}

#endif