#pragma once

#include "stddef.h"

typedef void (*t_element_destroyer)(void* elem);

typedef struct s_array
{
    size_t elem_size;

    size_t capacity;
    size_t elems;
    
    void* data;
    void* end;

    t_element_destroyer elem_destroyer;
} t_array;

t_array* array_create(size_t elem_size, t_element_destroyer elem_destroyer);
void array_destroy(t_array* array);

void array_append(t_array* array, const void* elem);
void* array_get_elem(t_array* array, int pos);

size_t array_length(t_array* array);