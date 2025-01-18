#include "list.h"
#include "stack.h"  // Include the list header for function declarations
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void test_stack_init(void);  // Test initialization of the list

int main(void)  // Main function to run all list tests
{
    printf("\nRunning stack tests...\n\n");

    test_stack_init();  // Test list initialization

    printf("\nAll tests completed.\n");

    return 0;
}

static void test_stack_init(void) 
{
    printf("Testing stack_init ...\n");
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return;
    list_init(stack, free);
    list_destroy(stack);
    free(stack);
}

