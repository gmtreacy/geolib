#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->destroy = destroy;
}

void list_destroy(List *list)
{
    if (list->destroy == NULL)
        return;

    // start at the head.
    // make next the new head
    // list->destroy up your data
    // list->destroy yourself
    for (;;)
    {
        if (list->head == NULL)
            break;

        ListElmt *curr = list->head;

        if (curr->next != NULL)
            list->head = curr->next;
        
        if (list->destroy != NULL){
            list->destroy(curr->data);
        }
        free(curr);
    }
    list_init(list, list->destroy);
}

// returns -1 on error
// if element is NULL, insert at head
// inserts just after match
int list_ins_next(List *list, ListElmt *element, void *data)
{
    if (element == NULL || list->head == NULL)
    {
        ListElmt *new_elmt = malloc(sizeof(ListElmt));
        if (new_elmt == NULL)
        {
            fprintf(stderr, "could not allocate memory for new element");
            return -1;
        }
        new_elmt->data = data;
        new_elmt->next = list->head;
        list->head = new_elmt;
        list->size++;
        return 0;
    }

    // find matching element
    ListElmt *curr = list->head;
    for (;;)
    {
        if (curr->data == element->data)
        {
            ListElmt *new_elmt = malloc(sizeof(ListElmt));
            if (new_elmt == NULL)
            {
                fprintf(stderr, "could not allocate memory for new element");
                return -1;
            }
            new_elmt->data = data;
            new_elmt->next = curr->next;
            curr->next = new_elmt;
            list->size++;
            if (new_elmt->next == NULL)
                list->tail = new_elmt;
            return 0;
        }
        if (curr->next != NULL)
            curr = curr->next;
        else
            return -1; // end of list and did not find element, no ins.
    }
}

// returns -1 on error
// removes next from match
// is element = NULL, remove from head
int list_rem_next(List *list, ListElmt *element, void **data)
{
    if (list->head == NULL) return -1;
    if (element == NULL)
    {
        ListElmt *curr = list->head;
        list->head = list->head->next;
        *data = curr->data;
        list->destroy(curr->data);
        list->destroy(curr); 
        list->size--;
        return 0;
    }

    // find matching element
    ListElmt *curr = list->head;
    for (;;)
    {
        if (curr->data == element->data)
        {
            if (curr == list->tail)
            {
                return -1;  // can't rem next after tail
            }
            ListElmt *to_rem = curr->next;
            curr->next = to_rem->next;
            list->size--;
            *data = to_rem->data;
            list->destroy(to_rem->data);
            list->destroy(to_rem);
            return 0;
        }
        if (curr->next != NULL)
            curr = curr->next;
        else
            return -1; // end of list and did not find element, no rem.
    }
    return -1;
}
