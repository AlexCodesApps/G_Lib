#ifndef G_HASHMAP_H
#define G_HASHMAP_H
#include "g_vector.h"
#include <limits.h>
#include <stdio.h>
#define g_hashtable_size 2

uint64_t g_hash_function(void * data, size_t len) {
    uint16_t hash_value = 0;
    for (int i = len - 1; i >= 0; i--) {
        hash_value += ((unsigned char*)data)[i];
        hash_value *= ((unsigned char*)data)[len - i];
    }
    return hash_value % g_hashtable_size;
}

#define g_hash_function_string(str) g_hash_function(str, strnlen(str, INT64_MAX))

#define __DECLARE_G_PAIR_DISAMBIGUATION(sign, sign2, type, type2) \
typedef struct {\
    type first;\
    type2 second;\
} g_pair_##sign##_##sign2;

#define DECLARE_G_PAIR(type, type2) __DECLARE_G_PAIR_DISAMBIGUATION(type, type2, type, type2)

#define __DECLARE_G_HASHMAP_DISAMBIGUATION(sign, sign2, type, type2, cmp_type) \
__DECLARE_G_PAIR_DISAMBIGUATION(sign, sign2, type, type2) \
__G_HASHMAP_INIT_STD(sign, sign2, type, type2) \
__G_HASHMAP_ADD_STD(sign, sign2, type, type2) \
__G_HASHMAP_GET_STD(sign, sign2, type, type2, cmp_type) \
__G_HASHMAP_REMOVE_STD(sign, sign2, type, type2, cmp_type)

#define __G_HASHMAP_EQ_STD(sign, sign2) \
(memcmp(&key, &g_vector_get(h_table->table[hash], g_pair_##sign##_##sign2, i).first, sizeof(key)) == 0)

#define __G_HASHMAP_INIT_STD(sign, sign2, type, type2) \
g_hashmap_t g_hashmap_init_##sign##_##sign2(){\
    g_hashmap_t new_map;\
    new_map.key_size = sizeof(type);\
    new_map.value_size = sizeof(type2);\
    return new_map;\
}
#define __G_HASHMAP_ADD_STD(sign, sign2, type, type2) \
void g_hashmap_add_##sign##_##sign2(g_hashmap_t * h_table, const type key, const type2 new_v) {\
    const size_t hash = g_hash_function(&key, sizeof(key));\
    if (h_table->table[hash].arr == NULL) {\
        g_vector_init(h_table->table[hash], g_pair_##sign##_##sign2, 1);\
    }\
    g_pair_##sign##_##sign2 new_element = {key, new_v};\
    g_vector_add(h_table->table[hash], new_element);\
}
#define __G_HASHMAP_GET_STD(sign, sign2, type, type2, cmp) \
type2 * g_hashmap_get_##sign##_##sign2(g_hashmap_t * h_table, const type key) {\
    const size_t hash = g_hash_function(&key, sizeof(key));\
    if(h_table->table[hash].arr == NULL) return NULL;\
    for (size_t i = 0; i < h_table->table[hash].len; i++) {\
        if (cmp) return &g_vector_get(h_table->table[hash], g_pair_##sign##_##sign2, i).second;\
    }\
    return NULL;\
}
#define __G_HASHMAP_REMOVE_STD(sign, sign2, type, type2, cmp) \
void g_hashmap_remove_##sign##_##sign2(g_hashmap_t * h_table, const type key) {\
    const size_t hash = g_hash_function(&key, sizeof(key));\
    if (h_table->table[hash].arr == NULL) return;\
    for (size_t i = 0; i < h_table->table[hash].len; i++) {\
        if (cmp) {\
        g_vector_remove(h_table->table[hash], i);\
        }\
    }\
}

typedef struct {
    g_vector_t table[g_hashtable_size];
    size_t key_size;
    size_t value_size;
} g_hashmap_t;

#define DECLARE_G_HASHMAP_V_V(x, y) __DECLARE_G_HASHMAP_DISAMBIGUATION(x, y, x, y, __G_HASHMAP_EQ_STD(x, y))
#define DECLARE_G_HASHMAP_P_V(x, y) __DECLARE_G_HASHMAP_DISAMBIGUATION(x##_ptr, y, x*, y, __G_HASHMAP_EQ_STD(x##_ptr, y))
#define DECLARE_G_HASHMAP_V_P(x, y) __DECLARE_G_HASHMAP_DISAMBIGUATION(x, y##_ptr, x, y*, __G_HASHMAP_EQ_STD(x, y##_ptr))
#define DECLARE_G_HASHMAP_P_P(x, y) __DECLARE_G_HASHMAP_DISAMBIGUATION(x##_ptr, y##_ptr, x*, y*, __G_HASHMAP_EQ_STD(x##_ptr, y##_ptr))

#define __G_HASHMAP_EQ_STRING(sign2) (strncmp(g_vector_get(h_table->table[hash], g_pair_string_##sign2, i).first, key, INT16_MAX) == 0)

#define __DECLARE_G_HASHMAP_STRING_DISAMBIGUATION(sign2, type2) \
__DECLARE_G_PAIR_DISAMBIGUATION(string, sign2, char *, type2)\
__G_HASHMAP_INIT_STD(string, sign2, char*, type2)\
__G_HASHMAP_GET_STD(string, sign2, char*, type2, __G_HASHMAP_EQ_STRING(sign2))\
__G_HASHMAP_REMOVE_STD(string, sign2, char*, type2, __G_HASHMAP_EQ_STRING(sign2))\
void g_hashmap_add_string_##sign2(g_hashmap_t * h_table, char * key, const type2 new_v) {\
    const size_t hash = g_hash_function(&key, sizeof(key));\
    if (h_table->table[hash].arr == NULL) {\
        g_vector_init(h_table->table[hash], g_pair_string_##sign2, 1);\
    }\
    char * new_str = malloc((strnlen(key, INT16_MAX) + 1)*sizeof(char));\
    strncpy(new_str, key, INT16_MAX);\
    g_pair_string_##sign2 new_element = {new_str, new_v};\
    g_vector_add(h_table->table[hash], new_element);\
}

#define DECLARE_G_HASHMAP_STRING_V(x) __DECLARE_G_HASHMAP_STRING_DISAMBIGUATION(x, x)

#endif