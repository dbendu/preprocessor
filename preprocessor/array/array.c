#include "memory.h"
#include "stdlib.h"

#include "array.h"

static int array_size_increment = 5;

t_array* array_create(size_t elem_size, t_element_destroyer elem_destroyer)
{
    t_array* array = malloc(sizeof(t_array));

    array->data = malloc(array_size_increment * elem_size);
    array->end = array->data;

    array->elem_destroyer = elem_destroyer;

    array->capacity = array_size_increment;
    array->elems = 0;
    array->elem_size = elem_size;

    return array;
}

#pragma region LocalFunctions

static void destroy_array_content(t_array* array)
{
    if (array->elem_destroyer == NULL)
        return;

    void* elem_ptr = array->data;

    for (size_t i = 0; i < array->elems; ++i)
    {
        array->elem_destroyer(elem_ptr);
        elem_ptr = (char*)elem_ptr + array->elem_size;
    }
}

static void resize_array(t_array* array)
{
    const size_t old_array_data_size_in_bytes = array->elems * array->elem_size;
    const size_t new_array_data_size_in_bytes = (array->elems + array_size_increment) * array->elem_size;

    void* data = malloc(new_array_data_size_in_bytes);
    memcpy(data, array->data, old_array_data_size_in_bytes);

    free(array->data);
    array->data = data;
    array->end = (char*)array->data + old_array_data_size_in_bytes;

    array->capacity += array_size_increment;
}

#pragma endregion

void array_destroy(t_array* array)
{
    destroy_array_content(array);

    free(array->data);
    free(array);
}

void array_append(t_array* array, const void* elem)
{
    if (array->capacity == 0)
        resize_array(array);

    memcpy(array->end, elem, array->elem_size);
    array->end = (char*)array->end + array->elem_size;
}

void* array_get_elem(t_array* array, int pos)
{
    return (char*)array->data + pos * array->elem_size;
}

size_t array_length(t_array* array)
{
    return array->elems;
}
