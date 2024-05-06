#ifndef G_MACROS_H
#define G_MACROS_H

#define DECODE_PTR(ptr, type) (*(type*)ptr)
#define new(type) (type*)malloc(sizeof(type))

#endif