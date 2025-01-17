#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initializes the list.
 * 
 * @param list The list to initialize.
 * @param destroy A function pointer to free the data stored in the list elements.
 */
void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->destroy = destroy;
}

/**
 * Destroys the list, freeing all elements and their data.
 * 
 * @param list The list to destroy.
 */
void list_destroy(List *list)
{
    if (list->destroy == NULL)
        return;

    while (list->head != NULL)
    {
        ListElmt *curr = list->head;
        list->head = curr->next;  // Always update head to next element
        
        if (list->destroy != NULL && list->destroy != (void (*)(void *))free) {
            list->destroy(curr->data);
        }
        free(curr);
    }
    list_init(list, list->destroy);
}

/**
 * Inserts a new element just after the specified element.
 * 
 * @param list The list to insert into.
 * @param element The element to insert after. If NULL, insert at the head.
 * @param data The data to store in the new element.
 * @return 0 on success, -1 on error.
 */
int list_ins_next(List *list, ListElmt *element, void *data)
{
    if (element == NULL)
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

    // Find matching element
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

/**
 * Removes the element just after the specified element.
 * 
 * @param list The list to remove from.
 * @param element The element to remove after. If NULL, remove from the head.
 * @param data A pointer to store the data of the removed element.
 * @return 0 on success, -1 on error.
 */
int list_rem_next(List *list, ListElmt *element, void **data)
{
    if (list->head == NULL) return -1;

    // Remove from head if element is NULL
    if (element == NULL)
    {
        ListElmt *old_element = list->head;
        *data = old_element->data;
        list->head = list->head->next;
        free(old_element);
        list->size--;
        if (list->size == 0) {
            list->tail = NULL;
        }
        return 0;
    }

    // Find matching element
    ListElmt *curr = list->head;
    while (curr != NULL)
    {
        if (curr->data == element->data)
        {
            // Can't remove next if we're at the tail
            if (curr->next == NULL) {
                return -1;
            }
            
            // Remove the next element
            ListElmt *to_remove = curr->next;
            *data = to_remove->data;
            curr->next = to_remove->next;
            
            // Update tail if we removed the last element
            if (curr->next == NULL) {
                list->tail = curr;
            }
            
            free(to_remove);
            list->size--;
            return 0;
        }
        curr = curr->next;
    }
    
    return -1;  // Element not found
}
