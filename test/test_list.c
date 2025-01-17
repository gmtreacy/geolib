#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Test function prototypes
static void test_list_init(void);
static void test_list_destroy(void);
static void test_list_ins_next(void);
static void test_list_rem_next(void);

int main(void)
{
    printf("\nRunning linked list tests...\n\n");

    test_list_init();
    test_list_destroy();
    test_list_ins_next();
    test_list_rem_next();

    printf("\nAll tests completed.\n");
    return 0;
}

static void test_list_init(void)
{
    printf("Testing list_init...\n");
    List list;
    list_init(&list, free);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.destroy == free);
}

static void test_list_destroy(void)
{
    printf("Testing list_destroy...\n");
    List list;
    list_init(&list, free);
    list_destroy(&list);
}

static void test_list_ins_next(void)
{
    printf("Testing list_ins_next...\n");
    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);

    printf("Testing list_ins_next to head...\n");
    int *x = malloc(sizeof(int));
    if (!x) return;
    *x = 7;
    int success = list_ins_next(list, NULL, x);
    assert(success == 0);
    assert(list->size == 1);
    assert(*(int*)list->head->data == 7);
    list_destroy(list);
    free(list);
    free(x);
}

static void test_list_rem_next(void)
{
    printf("Testing list_rem_next...\n");
    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);

    printf("Testing list_rem_next to head...\n");
    int *x = malloc(sizeof(int));
    if (!x) return;
    *x = 7;
    int success = list_ins_next(list, NULL, x);
    assert(success == 0);
    assert(list->size == 1);
    assert(*(int*)list->head->data == 7);
    void *data = NULL;
    success = list_rem_next(list, NULL, &data);
    assert(success == 0);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(*(int*)data == 7);
    free(data);
    list_destroy(list);
    free(list);
}
