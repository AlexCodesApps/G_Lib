#ifndef G_STRING_H
#define G_STRING_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char * str;
    size_t len;
} g_string_t;

g_string_t g_string_a(const char * c_str) {
    g_string_t nstr;
    nstr.len = strlen(c_str);
    nstr.str = (char *)malloc(sizeof(char)*nstr.len);
    memcpy(nstr.str, c_str, nstr.len * sizeof(char));
    return nstr;
}

g_string_t g_string_s(const char * c_str) {
    g_string_t nstr;
    nstr.len = strlen(c_str);
    nstr.str = (char *)c_str;
    return nstr;
}

g_string_t g_string_concat(g_string_t a, g_string_t b) {
    g_string_t nstr;
    nstr.len = a.len + b.len;
    nstr.str = (char*)malloc(sizeof(char) * nstr.len);
    memcpy(nstr.str, a.str, a.len);
    memcpy(nstr.str + a.len, b.str, b.len);
    return nstr;
}

char * g_string_c_str_a(g_string_t g) {
    char * nstr = (char*)malloc(sizeof(char) * g.len);
    memcpy(nstr, g.str, g.len);
    nstr[g.len] = '\0';
    return nstr;
}

void g_string_print(g_string_t g) {
    char * str = g_string_c_str_a(g);
    printf("%s", str);
    free(str);
}

void g_string_free(g_string_t * g) {
    free(g->str);
    g->len = 0;
}

#endif