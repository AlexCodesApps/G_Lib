#include <stdio.h>
#include "g_hashmap.h"

DECLARE_G_HASHMAP_STRING_V(int)
// Example Of Usage
int main(int argc, char const *argv[])
{
    g_hashmap_t map = g_hashmap_init_string_int();
    char str[] = "Hello World";
    char another[] = "dog";
    g_hashmap_add_string_int(&map, str, 10);
    g_hashmap_add_string_int(&map, another, 20);
    printf("%d\n", *g_hashmap_get_string_int(&map, "Hello World"));
    printf("%d\n", *g_hashmap_get_string_int(&map, another));
    g_hashmap_free_string_int(&map);
    return 0;
}