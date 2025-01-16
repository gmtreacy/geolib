#ifndef DARRAY_H
#define DARRAY_H

#include <stddef.h> // for size_t

// Struct to hold our dynamic array metadata
typedef struct {
    void** data;          // Pointer to array of void pointers for generic data
    size_t size;         // Current number of elements
    size_t capacity;     // Total capacity allocated
} DArray;

// Core operations
DArray* darray_create(size_t initial_capacity);
void darray_destroy(DArray* array);

// Element manipulation
int darray_append(DArray* array, void* element);
void* darray_get(DArray* array, size_t index);
int darray_set(DArray* array, size_t index, void* element);
int darray_remove(DArray* array, size_t index);

// Utility functions
size_t darray_size(const DArray* array);
size_t darray_capacity(const DArray* array);
int darray_resize(DArray* array, size_t new_capacity);
int darray_clear(DArray* array);

#endif // DARRAY_H
