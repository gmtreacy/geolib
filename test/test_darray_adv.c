#include "darray.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Test function prototypes
static void test_darray_resize_sequence(void);
static void test_darray_remove_sequence(void);
static void test_darray_mixed_operations(void);

int main(void) {
    printf("\nRunning advanced dynamic array tests...\n\n");

    // New tests for better coverage
    test_darray_resize_sequence();
    test_darray_remove_sequence();
    test_darray_mixed_operations();

    printf("\nAll tests completed.\n");
    return 0;
}

static void test_darray_resize_sequence(void) {
    printf("Testing resize sequence...\n");
    DArray* array = darray_create(2);
    assert(array != NULL);
    
    // Fill beyond initial capacity
    for (int i = 0; i < 10; i++) {
        int* val = malloc(sizeof(int));
        *val = i;
        int result = darray_append(array, val);
        assert(result == 0);
        assert(darray_size(array) == (size_t)(i + 1));
        assert(darray_capacity(array) >= darray_size(array));
    }

    // Verify values and order
    for (size_t i = 0; i < 10; i++) {
        int* val = darray_get(array, i);
        assert(val != NULL);
        assert(*val == (int)i);
    }

    // Clean up
    for (size_t i = 0; i < darray_size(array); i++) {
        free(darray_get(array, i));
    }
    darray_destroy(array);
}

static void test_darray_remove_sequence(void) {
    printf("Testing remove sequence...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);

    // Add elements
    for (int i = 0; i < 5; i++) {
        int* val = malloc(sizeof(int));
        *val = i;
        darray_append(array, val);
    }

    // Remove from middle
    int* val2 = darray_get(array, 2);
    assert(darray_remove(array, 2) == 0);
    free(val2);
    assert(darray_size(array) == 4);

    // Verify order preserved
    int expected[] = {0, 1, 3, 4};
    for (size_t i = 0; i < darray_size(array); i++) {
        int* val = darray_get(array, i);
        if (!val) {
            printf("Error: NULL pointer at index %zu\n", i);
            return;
        }
        printf("Testing remove from middle assert expected %zu...\n", i);
        printf("val = %p\n", (void*)val);
        printf("val = %d\n", *val);
        assert(*val == expected[i]);
    }

    // Clean up
    printf("Testing remove from middle clean up...\n");
    for (size_t i = 0; i < darray_size(array); i++) {
        free(darray_get(array, i));
    }
    darray_destroy(array);
}

static void test_darray_mixed_operations(void) {
    printf("Testing mixed operations...\n");
    DArray* array = darray_create(3);
    assert(array != NULL);

    // Append
    int* val1 = malloc(sizeof(int));
    if (!val1) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    } else {
        printf("val1 = %p\n", (void*)val1);
    }

    *val1 = 10;
    assert(darray_append(array, val1) == 0);

    // Set
    int* val2 = malloc(sizeof(int));
    *val2 = 20;
    if (!val2) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    } else {
        printf("val2 = %p\n", (void*)val1);
    }

    assert(darray_set(array, 0, val2) == 0);
    free(val1);  // Free old value

    // Remove
    assert(darray_remove(array, 0) == 0);
    free(val2);

    // Verify empty
    assert(darray_size(array) == 0);
    assert(darray_get(array, 0) == NULL);

    darray_destroy(array);
}
