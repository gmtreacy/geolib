#include "pqueue.h"
#include <stdlib.h>
#include <stdbool.h>

pqueue_t *pqueue_new()
{
    return NULL;
}

int pqueue_isempty(pqueue_t *pq)
{
    return 0;
}

void pqueue_enqueue(pqueue_t *pq, void *item, int size) {}

void pqueue_enqueue_with_priority(pqueue_t *pq, void *item, int size, int (*cmpfptr)(const void *, const void *)) {}

void pqueue_free(pqueue_t *pq, void (*delfptr)(void *)) {}

void *pqueue_dequeue(pqueue_t *pq) { return NULL; }

void *pqueue_find(pqueue_t *pq, void *item, int (*cmpfptr)(const void *, const void *)) { return NULL; }

void *pqueue_remove(pqueue_t *pq, void *item, int (*cmpfptr)(const void *, const void *)) { return NULL; }
