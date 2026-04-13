#include"stack.h"

StackElement* create_stack_element(void *value) {
    StackElement *res;

    if ((res = (StackElement*) malloc(sizeof(StackElement))) == NULL) {
        fprintf(stderr, "Error while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    res->value = value;
    res->next = NULL;
    return res;
}

Stack* create_stack() {
    Stack *res;

    if ((res = (Stack*) malloc(sizeof(Stack))) == NULL) {
        fprintf(stderr, "Error while memory allocation\n");
        exit(EXIT_FAILURE);
    }

    res->first = NULL;
    res->count = 0;
    res->free_func = &free;

    return res;
}

Stack* set_stack_free_function(Stack *stack, void (*func)(void*)) {
    stack->free_func = func;
    return stack;
}

Stack* stack_push(Stack *stack, void *value) {
    StackElement *new;

    new = create_stack_element(value);
    new->next = stack->first;

    stack->first = new;
    stack->count++;

    return stack;
}

void* stack_value(Stack *stack) {

    if (stack->first == NULL) {
        fprintf(stderr, "Error stack_value. STACK is empty\n");
        exit(EXIT_FAILURE);
    }

    return stack->first->value;
}

void* stack_pop(Stack *stack) {
    void *res;
    StackElement *tmp;

    if (stack->first == NULL) {
        fprintf(stderr, "Error stack_pop. STACK is empty\n");
        exit(EXIT_FAILURE);
    }

    tmp = stack->first;
    stack->first = stack->first->next;

    res = tmp->value;
    free(tmp);

    stack->count--;

    return res;
}

size_t get_stack_size(Stack *stack) {
    return stack->count;
}

int stack_is_empty(Stack *stack) {
    return stack->first == NULL;
}

Stack* stack_remove(Stack *stack) {
    StackElement *tmp;

    if (stack->first == NULL) {
        fprintf(stderr, "Error stack_remove. STACK is empty\n");
        exit(EXIT_FAILURE);
    }
    tmp = stack->first;
    stack->first = stack->first->next;

    stack->free_func(tmp->value);
    free(tmp);

    stack->count--;

    return stack;
}

Stack* stack_clear(Stack *stack) {

    while (!stack_is_empty(stack)) {
        stack_remove(stack);
    }

    return stack;
}

void free_stack(Stack *stack) {
    stack_clear(stack);
    free(stack);
}