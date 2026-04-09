#ifndef _STACK_H_
#define _STACK_H_

#include<stdlib.h>
#include<stdio.h>

struct StackElement {
    void *value;
    struct StackElement *next;
};
typedef struct StackElement StackElement;

typedef struct {
    StackElement *first;
    size_t count;
    void (*free_func)(void*);
} Stack;


Stack* create_stack();

Stack* set_stack_free_function(Stack *stack, void (*func)(void*));

Stack* stack_push(Stack *stack, void *value);

void* stack_value(Stack *stack);

void* stack_pop(Stack *stack);

size_t get_stack_size(Stack *stack);

int stack_is_empty(Stack *stack);

Stack* stack_remove(Stack *stack);

Stack* stack_clear(Stack *stack);

void free_stack(Stack *stack);

#endif /* _STACK_H_ */