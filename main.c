#include <stdio.h>
#include "g_hashmap.h"
#include "g_macros.h"

DECLARE_G_HASHMAP_V_V(int, char)
DECLARE_G_HASHMAP_STRING_V(int)
DECLARE_G_HASHMAP_STRING_P(char)
// Example Of Usage
int main(int argc, char const *argv[])
{
    g_hashmap_t map = g_hashmap_init_string_int();
    g_hashmap_t * cap = new(g_hashmap_t);
    *cap = g_hashmap_init_int_char();
    g_hashmap_add_int_char(cap, 12, 'a');
    g_hashmap_add_int_char(cap, 24, 'b');
    char str[] = "Hello World";
    char another[] = "dog";
    g_hashmap_add_string_int(&map, str, 10);
    g_hashmap_add_string_int(&map, another, 20);
    printf("%d\n", *g_hashmap_get_string_int(&map, "Hello World"));
    printf("%d\n", *g_hashmap_get_string_int(&map, another));
    printf("%c\n", *g_hashmap_get_int_char(cap, 24));
    g_hashmap_free_string_int(&map);
    g_hashmap_free(cap);
    free(cap);
    return 0;
}