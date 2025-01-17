#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void test_list_init(void);
static void test_list_destroy(void);
static void test_list_insert_empty(void);
static void test_list_remove_empty(void);
static void test_list_insert_middle(void);
static void test_list_insert_tail(void);
static void test_list_remove_middle(void);
static void test_list_remove_tail(void);
static void test_list_ins_next(void);
static void test_list_rem_next(void);

int main(void)
{
    printf("\nRunning linked list tests...\n\n");

    test_list_init();
    test_list_init();
    test_list_destroy();
    test_list_insert_empty();
    test_list_remove_empty();
    test_list_insert_middle();
    test_list_insert_tail();
    test_list_remove_middle();
    test_list_remove_tail();
    test_list_ins_next();
    test_list_rem_next();

    printf("\nAll tests completed.\n");
    return 0;
}

static void test_list_insert_empty(void)
{
    printf("Testing list_insert_empty...\n");
    List list;
    list_init(&list, free);
    int *x = malloc(sizeof(int));
    *x = 1;
    int success = list_ins_next(&list, NULL, x);
    assert(success == 0);
    assert(list.size == 1);
    assert(*(int*)list.head->data == 1);
    list_destroy(&list);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
}

static void test_list_remove_empty(void)
{
    printf("Testing list_remove_empty...\n");
    List list;
    list_init(&list, free);
    void *data;
    int success = list_rem_next(&list, NULL, &data);
    assert(success == -1);
    list_destroy(&list);
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
    printf("Testing list_destroy...\n");
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    *x = 1; *y = 2; *z = 3;
    list_ins_next(&list, NULL, x);
    list_ins_next(&list, list.head, y);
    list_ins_next(&list, list.head->next, z);
    list_destroy(&list);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
}

static void test_list_ins_next(void)
{
    printf("Testing list_ins_next...\n");
    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);

    printf("Testing list_ins_next...\n");
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

static void test_list_insert_middle(void)
{
    printf("Testing list_insert_middle...\n");
    List list;
    list_init(&list, free);
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    *x = 1; *y = 2; *z = 3;
    list_ins_next(&list, NULL, x);
    list_ins_next(&list, list.head, z);
    list_ins_next(&list, list.head, y);
    assert(list.size == 3);
    assert(*(int*)list.head->next->data == 2);
    list_destroy(&list);
}

static void test_list_insert_tail(void)
{
    printf("Testing list_insert_tail...\n");
    List list;
    list_init(&list, free);
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    *x = 1; *y = 2;
    list_ins_next(&list, NULL, x);
    list_ins_next(&list, list.head, y);
    assert(list.size == 2);
    assert(*(int*)list.tail->data == 2);
    list_destroy(&list);
}

static void test_list_remove_middle(void)
{
    printf("Testing list_remove_middle...\n");
    List list;
    list_init(&list, free);
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    int *z = malloc(sizeof(int));
    *x = 1; *y = 2; *z = 3;
    list_ins_next(&list, NULL, x);
    list_ins_next(&list, list.head, y);
    list_ins_next(&list, list.head->next, z);
    void *data;
    list_rem_next(&list, list.head, &data);
    assert(list.size == 2);
    assert(*(int*)data == 2);
    free(data);
    list_destroy(&list);
}

static void test_list_remove_tail(void)
{
    printf("Testing list_remove_tail...\n");
    List list;
    list_init(&list, free);
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    *x = 1; *y = 2;
    list_ins_next(&list, NULL, x);
    list_ins_next(&list, list.head, y);
    void *data;
    list_rem_next(&list, list.head, &data);
    assert(list.size == 1);
    assert(*(int*)data == 2);
    free(data);
    list_destroy(&list);
}

static void test_list_rem_next(void)
{
    printf("Testing list_rem_next...\n");
    List *list = malloc(sizeof(List));
    if (!list) return;

    list_init(list, free);

    printf("Testing list_rem_next...\n");
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
