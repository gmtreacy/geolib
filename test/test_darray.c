#include "darray.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Test function prototypes
static void test_create(void);
static void test_destroy(void);
static void test_append(void);
static void test_get(void);
static void test_remove(void);
static void test_size(void);
static void test_clear(void);
static void test_darray_basic(void);
static void test_darray_edge_cases(void);
static void test_darray_resize(void);
static void test_darray_resize_sequence(void);
static void test_darray_remove_sequence(void);
static void test_darray_mixed_operations(void);

int main(void) {
    printf("Running dynamic array tests...\n\n");

    // Basic operations tests
    test_create();
    test_destroy();
    test_append();
    test_get();
    test_remove();
    test_size();
    test_clear();

    // Comprehensive tests
    test_darray_basic();
    test_darray_edge_cases();
    test_darray_resize();

    // New tests for better coverage
    test_darray_resize_sequence();
    // test_darray_remove_sequence();
    test_darray_mixed_operations();

    printf("\nAll tests completed.\n");
    return 0;
}

static void test_create(void) {
    printf("Testing darray_create...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    assert(darray_size(array) == 0);
    assert(darray_capacity(array) == 5);
    darray_destroy(array);
}

static void test_destroy(void) {
    printf("Testing darray_destroy...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    darray_destroy(array);
    // Note: Can't test array after destruction as it's invalid
}

static void test_append(void) {
    printf("Testing darray_append...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    
    int* value = malloc(sizeof(int));
    *value = 42;
    
    int result = darray_append(array, value);
    assert(result == 0);  // Expect success
    assert(darray_size(array) == 1);
    
    free(value);
    darray_destroy(array);
}

static void test_get(void) {
    printf("Testing darray_get...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    
    int* value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);
    
    void* retrieved = darray_get(array, 0);
    assert(retrieved != NULL);
    assert(*(int*)retrieved == 42);
    
    free(value);
    darray_destroy(array);
}

static void test_remove(void) {
    printf("Testing darray_remove...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    
    int* value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);
    
    int result = darray_remove(array, 0);
    assert(result == 0);  // Expect success
    assert(darray_size(array) == 0);
    
    free(value);
    darray_destroy(array);
}

static void test_size(void) {
    printf("Testing darray_size...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    
    size_t initial_size = darray_size(array);
    assert(initial_size == 0);
    
    int* value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);
    
    size_t new_size = darray_size(array);
    assert(new_size == 1);
    
    free(value);
    darray_destroy(array);
}

static void test_clear(void) {
    printf("Testing darray_clear...\n");
    DArray* array = darray_create(5);
    assert(array != NULL);
    
    int* value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);
    
    darray_clear(array);
    assert(darray_size(array) == 0);
    
    free(value);
    darray_destroy(array);
}

static void test_darray_basic(void) {
    printf("Testing basic operations...\n");
    DArray* array = darray_create(2);
    assert(array != NULL);
    assert(darray_size(array) == 0);
    assert(darray_capacity(array) == 2);

    int* val1 = malloc(sizeof(int));
    *val1 = 42;
    assert(darray_append(array, val1) == 0);
    assert(darray_size(array) == 1);

    assert(darray_get(array, 0) == val1);
    assert(darray_get(array, 1) == NULL);

    int* val2 = malloc(sizeof(int));
    *val2 = 24;
    assert(darray_set(array, 0, val2) == 0);
    assert(darray_get(array, 0) == val2);

    free(val1);
    free(val2);
    darray_destroy(array);
}

static void test_darray_edge_cases(void) {
    printf("Testing edge cases...\n");
    
    // Part 1: Test NULL array operations individually
    printf("Testing NULL array operations...\n");
    DArray* null_array = NULL;
    
    // Test each NULL operation separately with debug output
    printf("Testing append on NULL...\n");
    assert(darray_append(null_array, NULL) == -1);
    
    printf("Testing get on NULL...\n");
    assert(darray_get(null_array, 0) == NULL);
    
    printf("Testing set on NULL...\n");
    assert(darray_set(null_array, 0, NULL) == -1);
    
    printf("Testing remove on NULL...\n");
    assert(darray_remove(null_array, 0) == -1);
    
    printf("Testing size on NULL...\n");
    assert(darray_size(null_array) == -1);
    
    printf("Testing capacity on NULL...\n");
    assert(darray_capacity(null_array) == -1);
    
    printf("Testing clear on NULL...\n");
    assert(darray_clear(null_array) == -1);

    // Part 2: Test valid array with edge cases
    printf("Testing valid array edge cases...\n");
    DArray* array = darray_create(1);
    assert(array != NULL);
    
    // Test operations on empty array
    assert(darray_get(array, 0) == NULL);
    assert(darray_remove(array, 0) == -1);
    
    darray_destroy(array);
    printf("Edge case tests completed.\n");
}


static void test_darray_resize(void) {
    printf("Testing resize operations...\n");
    DArray* array = darray_create(2);
    assert(array != NULL);
    
    // Fill array to trigger resize
    for (int i = 0; i < 5; i++) {
        int* val = malloc(sizeof(int));
        *val = i;
        assert(darray_append(array, val) == 0);
    }

    assert(darray_capacity(array) >= 5);
    assert(darray_size(array) == 5);

    // Clean up
    for (size_t i = 0; i < darray_size(array); i++) {
        int* val = darray_get(array, i);
        free(val);
    }
    darray_destroy(array);
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
    for (int i = 0; i < 10; i++) {
        int* val = darray_get(array, i);
        assert(val != NULL);
        assert(*val == i);
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
        printf("Testing remove from middle assert expected %d...\n", i);
        printf("val = %p\n", val);
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
    *val1 = 10;
    assert(darray_append(array, val1) == 0);

    // Set
    int* val2 = malloc(sizeof(int));
    *val2 = 20;
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
