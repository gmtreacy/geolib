#include "pqueue.h"  // Include the list header for function declarations
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void test_pqueue_new(void);  // Test initialization of the list

int main(void)  // Main function to run all list tests
{
    printf("\nRunning pqueue tests...\n\n");

    test_pqueue_new();  // Test list initialization

    printf("\nAll tests completed.\n");

    return 0;
}

static void test_pqueue_new(void) 
{
    printf("Testing pqueue_new ...\n");
    pqueue_t *pq = pqueue_new();
    free(pq);
}

