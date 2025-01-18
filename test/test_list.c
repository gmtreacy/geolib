#include "list.h"  // Include the list header for function declarations
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void test_list_init(void);  // Test initialization of the list
static void test_list_destroy(void);
static void test_list_insert_empty(void);
static void test_list_remove_empty(void);
static void test_list_insert_tail(void);
static void test_list_remove_middle(void);
static void test_list_remove_tail(void);
static void test_list_ins_next(void);
static void test_list_rem_next(void);

int main(void)  // Main function to run all list tests
{
    printf("\nRunning linked list tests...\n\n");

    test_list_init();  // Test list initialization
    test_list_destroy();
    test_list_insert_empty();
    test_list_remove_empty();
    test_list_insert_tail();
    test_list_remove_middle();
    test_list_remove_tail();
    test_list_ins_next();
    test_list_rem_next();

    printf("\nAll tests completed.\n");
    return 0;
}

static void test_list_insert_empty(void)  // Test inserting into an empty list
{
    printf("Testing list_insert_empty...\n");
    List *list = malloc(sizeof(List));
    list_init(list, free);  // Initialize list with free function
    //
    int *x = malloc(sizeof(int));  // Allocate memory for an integer
    *x = 1;

    int success = list_ins_next(list, NULL, x);  // Insert into empty list
    assert(success == 0);
    assert(list->size == 1);
    assert(*(int*)list->head->data == 1);
    list_destroy(list);  // Destroy the list and free memory using destroy function
}

static void test_list_remove_empty(void)  // Test removing from an empty list
{
    printf("Testing list_remove_empty...\n");
    List *list = malloc(sizeof(List));
    list_init(list, free);  // Initialize list with free function
    void *data;
    int success = list_rem_next(list, NULL, &data);  // Attempt to remove from empty list
    assert(success == -1);
    list_destroy(list);  // Destroy the list using destroy function
}



static void test_list_init(void)  // Test list initialization
{
    printf("Testing list_init...\n");

    List list;
    list_init(&list, free);  // Initialize list with free function
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.destroy == free);
}

static void test_list_destroy(void)  // Test list destruction
{
    printf("Testing list_destroy...\n");

    List *list = malloc(sizeof(List));
    list_init(list, free);  // Initialize list with free function
    
    int *x = malloc(sizeof(int));  // Allocate memory for integers
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    *x = 1; *y = 2; *z = 3;

    list_ins_next(list, NULL, x);  // Insert elements into the list
    list_ins_next(list, list->head, y);
    list_ins_next(list, list->head->next, z);
    list_destroy(list);  // Destroy the list and free memory using destroy function
}

static void test_list_ins_next(void)  // Test inserting next element
{
    printf("Testing list_ins_next...\n");

    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);  // Initialize list with free function

    int *x = malloc(sizeof(int));  // Allocate memory for an integer
    if (!x) {
        free(list);
        return;
    }
    *x = 7;

    int success = list_ins_next(list, NULL, x);  // Insert into list
    assert(success == 0);
    assert(list->size == 1);
    assert(*(int*)list->head->data == 7);
    list_destroy(list);  // Destroy the list and free memory using destroy function
}

static void test_list_insert_tail(void)  // Test inserting at the tail
{
    printf("Testing list_insert_tail...\n");

    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);  // Initialize list with free function
    //
    int *x = malloc(sizeof(int));  // Allocate memory for integers
    int *y = malloc(sizeof(int));
    *x = 1; *y = 2;

    list_ins_next(list, NULL, x);  // Insert elements into the list
    list_ins_next(list, list->head, y);
    assert(list->size == 2);
    assert(*(int*)list->tail->data == 2);
    list_destroy(list);  // Destroy the list and free memory using destroy function
}

static void test_list_remove_middle(void)  // Test removing from the middle
{
    printf("Testing list_remove_middle...\n");

    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);  // Initialize list with free function
    //
    int *x = malloc(sizeof(int));  // Allocate memory for integers
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    *x = 1; *y = 2; *z = 3;

    list_ins_next(list, NULL, x);  // Insert elements into the list
    list_ins_next(list, list->head, y);
    list_ins_next(list, list->head->next, z);

    void *data;
    list_rem_next(list, list->head, &data);  // Remove element from the middle
    assert(list->size == 2);
    assert(*(int*)data == 2);
    free(data);  // Free the removed data
    list_destroy(list);  // Destroy the list and free memory using destroy function
}

static void test_list_remove_tail(void)  // Test removing from the tail
{
    printf("Testing list_remove_tail...\n");

    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);  // Initialize list with free function
    //
    int *x = malloc(sizeof(int));  // Allocate memory for integers
    int *y = malloc(sizeof(int));
    *x = 1; *y = 2;

    list_ins_next(list, NULL, x);  // Insert elements into the list
    list_ins_next(list, list->head, y);

    void *data;
    list_rem_next(list, list->head, &data);  // Remove element from the tail
    assert(list->size == 1);
    assert(*(int*)data == 2);
    free(data);  // Free the removed data
    list_destroy(list);  // Destroy the list and free memory using destroy function
}

static void test_list_rem_next(void)  // Test removing next element
{
    printf("Testing list_rem_next...\n");

    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);  // Initialize list with free function
    //
    int *x = malloc(sizeof(int));  // Allocate memory for an integer
    if (!x) {
        free(list);
        return;
    }
    *x = 7;

    int success = list_ins_next(list, NULL, x);  // Insert into list
    assert(success == 0);
    assert(list->size == 1);
    assert(*(int*)list->head->data == 7);

    void *data = NULL;  // Pointer to hold removed data
    success = list_rem_next(list, NULL, &data);  // Remove element from list
    assert(success == 0);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(*(int*)data == 7);
    free(data);  // Free the removed data
    list_destroy(list);  // Destroy the list and free memory
}
