#ifndef STACK_H
#define STACK_H

#include <stddef.h> // for size_t
#include "list.h"
                
typedef List Stack;

void stack_init(Stack *stack, void (*destroy)(void *data));

void stack_destroy(Stack *stack);

#endif // STACK_H
