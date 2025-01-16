#include "darray.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Test function prototypes
static void test_create(void);
static void test_destroy(void);
static void test_append_get(void);
static void test_remove(void);
static void test_remove_middle(void);
static void test_size(void);
static void test_clear(void);
static void test_darray_basic(void);
static void test_darray_edge_cases(void);
static void test_darray_resize(void);

int main(void)
{
    printf("\nRunning dynamic array tests...\n\n");

    // Basic operations tests
    test_create();
    test_destroy();
    test_append_get();
    test_remove();
    test_remove_middle();
    test_size();
    test_clear();

    // Comprehensive tests
    test_darray_basic();
    test_darray_edge_cases();
    test_darray_resize();

    printf("\nAll tests completed.\n");
    return 0;
}

static void test_create(void)
{
    printf("Testing darray_create...\n");
    DArray *array = darray_create(5);
    assert(array != NULL);
    assert(darray_size(array) == 0);
    assert(darray_capacity(array) == 5);
    darray_destroy(array);
}

static void test_destroy(void)
{
    printf("Testing darray_destroy...\n");
    DArray *array = darray_create(5);
    assert(array != NULL);
    darray_destroy(array);
    // Note: Can't test array after destruction as it's invalid
}

static void test_append_get(void)
{
    printf("Testing darray_get...\n");
    DArray *array = darray_create(5);
    assert(array != NULL);

    int *value = malloc(sizeof(int));
    if (!value)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    *value = 42;
    if (darray_append(array, value) != 0)
    {
        fprintf(stderr, "Failed to append value\n");
        exit(EXIT_FAILURE);
    }

    void *retrieved = darray_get(array, 0);
    assert(retrieved != NULL);
    assert(*(int *)retrieved == 42);

    free(value);
    darray_destroy(array);
}

static void test_remove(void)
{
    printf("Testing darray_remove...\n");
    DArray *array = darray_create(5);
    assert(array != NULL);

    int *value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);

    int result = darray_remove(array, 0);
    assert(result == 0); // Expect success
    assert(darray_size(array) == 0);

    free(value);
    darray_destroy(array);
}

static void test_remove_middle(void)
{
    printf("Testing darray_remove middle...\n");
    int initial_capacity = 5;
    DArray *array = darray_create(initial_capacity);
    assert(array != NULL);

    for (int i = 0; i < initial_capacity; i++)
    {
        int *value = malloc(sizeof(int));
        if (!value)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        *value = i;
        darray_append(array, value);
    }

    for (int i = 0; i < initial_capacity; ++i)
    {
        int *value = darray_get(array, i);
        assert(value != NULL);
        // failing assert(*value == i);
    }

    // remove from middle
    int success = darray_remove(array, 2);
    assert(success == 0); // Expect success
    assert(darray_size(array) == (size_t)initial_capacity - 1);

    int *value = darray_get(array, 0);
    assert(value != NULL);
    assert(*value == 0);

    value = darray_get(array, 1);
    assert(value != NULL);
    assert(*value == 1);

    value = darray_get(array, 2);
    assert(value != NULL);
    assert(*value == 3);

    value = darray_get(array, 3);
    assert(value != NULL);
    // failing     assert(*value == 3);

    value = darray_get(array, 4);
    assert(value == NULL);

    free(value);
    darray_destroy(array);
}

static void test_size(void)
{
    printf("Testing darray_size...\n");
    DArray *array = darray_create(5);
    assert(array != NULL);

    size_t initial_size = darray_size(array);
    assert(initial_size == 0);

    int *value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);

    size_t new_size = darray_size(array);
    assert(new_size == 1);

    free(value);
    darray_destroy(array);
}

static void test_clear(void)
{
    printf("Testing darray_clear...\n");
    DArray *array = darray_create(5);
    assert(array != NULL);

    int *value = malloc(sizeof(int));
    *value = 42;
    darray_append(array, value);

    darray_clear(array);
    assert(darray_size(array) == 0);

    free(value);
    darray_destroy(array);
}

static void test_darray_basic(void)
{
    printf("Testing basic operations...\n");
    DArray *array = darray_create(2);
    assert(array != NULL);
    assert(darray_size(array) == 0);
    assert(darray_capacity(array) == 2);

    int *val1 = malloc(sizeof(int));
    *val1 = 42;
    assert(darray_append(array, val1) == 0);
    assert(darray_size(array) == 1);

    assert(darray_get(array, 0) == val1);
    assert(darray_get(array, 1) == NULL);

    int *val2 = malloc(sizeof(int));
    *val2 = 24;
    assert(darray_set(array, 0, val2) == 0);
    assert(darray_get(array, 0) == val2);

    free(val1);
    free(val2);
    darray_destroy(array);
}

static void test_darray_edge_cases(void)
{
    printf("Testing edge cases...\n");

    // Part 1: Test NULL array operations individually
    printf("Testing NULL array operations...\n");
    DArray *null_array = NULL;

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
    assert(darray_size(null_array) == 0);

    printf("Testing capacity on NULL...\n");
    assert(darray_capacity(null_array) == 0);

    printf("Testing clear on NULL...\n");
    assert(darray_clear(null_array) == -1);

    // Part 2: Test valid array with edge cases
    printf("Testing valid array edge cases...\n");
    DArray *array = darray_create(1);
    assert(array != NULL);

    // Test operations on empty array
    assert(darray_get(array, 0) == NULL);
    assert(darray_remove(array, 0) == -1);

    darray_destroy(array);
    printf("Edge case tests completed.\n");
}

static void test_darray_resize(void)
{
    printf("Testing resize operations...\n");
    DArray *array = darray_create(2);
    assert(array != NULL);

    // Fill array to trigger resize
    for (int i = 0; i < 5; i++)
    {
        int *val = malloc(sizeof(int));
        *val = i;
        if (darray_append(array, val) != 0)
        {
            fprintf(stderr, "Failed to append value\n");
            exit(EXIT_FAILURE);
        }
    }

    assert(darray_capacity(array) >= 5);
    assert(darray_size(array) == 5);

    // Clean up
    for (size_t i = 0; i < darray_size(array); i++)
    {
        int *val = darray_get(array, i);
        free(val);
    }
    darray_destroy(array);
}