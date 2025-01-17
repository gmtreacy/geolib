#ifndef LIST_H
#define LIST_H

#include <stddef.h> // for size_t

typedef struct ListElmt_
{
    void *data;
    struct ListElmt_ *next;
} ListElmt;

typedef struct
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
} List;

void list_init(List *list, void (*destroy)(void *data));

void list_destroy(List *list);

// returns -1 on error
int list_ins_next(List *list, ListElmt *element, void *data);

// returns -1 on error
int list_rem_next(List *list, ListElmt *element, void **data);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

// returns 1 if true
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

// returns 1 if true
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)

#endif // LIST_H
