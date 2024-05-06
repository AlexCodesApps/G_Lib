#ifndef G_STRING_H
#define G_STRING_H
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include "g_vector.h"

typedef struct {
    size_t length;
    char string[];
} g_string_t;

g_string_t g_string_wrap(const char * str) {
    const size_t str_len = strlen(str);
    g_string_t * nstr = (g_string_t*)alloca(sizeof(size_t) + str_len*sizeof(char));
    nstr->length = str_len;
    strcpy(nstr->string, str);
    return *nstr;
}

g_string_t g_string_concat(g_string_t a, g_string_t b) {
    const size_t n_len = a.length + b.length;
    g_string_t * nstr = (g_string_t*)alloca(sizeof(size_t) + n_len*sizeof(char));
    memcpy(nstr->string, a.string, a.length*sizeof(char));
    memcpy(nstr->string+a.length, b.string, b.length*sizeof(char));
    return *nstr;
}

const char * g_string_cstr(g_string_t a) {
    char * str = (char*)alloca(sizeof(char) * (a.length + 1));
    memcpy(str, a.string, a.length*sizeof(char));
    str[a.length] = '\0';
    return str;
}

#endif