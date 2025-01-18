/* queue.h */

#ifndef PQUEUE_H
#define PQUEUE_H

#include "list.h"
#include <stdbool.h>

typedef struct pqueue_t
{
    List *dl;
} pqueue_t;

pqueue_t *pqueue_new();

bool pqueue_isempty(pqueue_t *);

void pqueue_enqueue(pqueue_t *, void *item, int size);

void pqueue_enqueue_with_priority(pqueue_t *, void *item, int size, int (*cmpfptr)(const void *, const void *));

void pqueue_free(pqueue_t *, void (*delfptr)(void *));

void *pqueue_dequeue(pqueue_t *);

void *pqueue_find(pqueue_t *, void *item, int (*cmpfptr)(const void *, const void *));

void *pqueue_remove(pqueue_t *, void *item, int (*cmpfptr)(const void *, const void *));

#endif // PQUEUE_H
