#include "darray.h"
#include <stdlib.h>

DArray *darray_create(size_t initial_capacity)
{
    DArray *array = malloc(sizeof(DArray));
    if (array == NULL)
        return NULL;

    void **data = malloc(initial_capacity * sizeof(int));
    if (data == NULL)
    {
        free(array);
        return NULL;
    }

    array->data = data;
    array->size = 0;
    array->capacity = initial_capacity;
    return array;
}

void darray_destroy(DArray *array)
{
    free(array->data);
    free(array);
}

int darray_append(DArray *array, void *element)
{
    if (!array) return -1;
    if (array->size == array->capacity)
    {
        size_t new_cap = array->size * 2;
        void **new_data = realloc(array->data, new_cap * sizeof(void *));
        if (new_data == NULL)
        {
            return -1;
        }
        array->data = new_data;
        array->capacity = new_cap;
    }
    array->data[array->size] = element;
    array->size++;
    return 0; // Return 0 for success, -1 for failure.
}

int darray_resize(DArray *array, size_t new_capacity)
{
    void **new_data = realloc(array->data, new_capacity * sizeof(void *));
    if (new_data == NULL)
    {
        return -1;
    }
    array->data = new_data;
    array->capacity = new_capacity;
    return 0;
}

void *darray_get(DArray *array, size_t index)
{
    if (array == NULL || index >= array->size)
    {
        return NULL;
    }
    return array->data[index];
}

int darray_set(DArray *array, size_t index, void *element)
{
    if (array == NULL || index > array->size)
    {
        return -1;
    }
    array->data[index] = element;
    return 0;
}

int darray_remove(DArray *array, size_t index)
{
    if (array == NULL || index >= array->size)
    {
        return -1;
    }
    for (size_t i = index; i < array->size; i++)
    {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
    return 0;
}

size_t darray_size(const DArray *array)
{
    if (array)
        return array->size;
    return -1;
}

size_t darray_capacity(const DArray *array)
{
    if (array)
        return array->capacity;
    return -1;
}

int darray_clear(DArray *array)
{
    if (!array)
        return -1;

    array->size = 0;
    return 0;
}
