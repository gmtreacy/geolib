#import "stack.h"
#include "list.h"

void stack_init(Stack *stack, void (*destroy)(void *data)) {
    list_init(stack, destroy);
}

void stack_destroy(Stack *stack) {
    list_destroy(stack);
}


