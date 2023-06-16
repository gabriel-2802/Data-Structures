#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack.h"

void init_stack(struct stack_t  *stack, unsigned int data_size) {
    stack->list = ll_create(data_size);
}

int get_size_stack(struct stack_t  *stack) {
    return (int)stack->list->size;
}

int is_empty_stack(struct stack_t  *stack) {
    return (0 == stack->list->size);
}

void* peek_stack(struct stack_t  *stack) {
    return stack->list->head->data;
}
void pop_stack(struct stack_t  *stack) {
    ll_node_t *popped = ll_remove_nth_node(stack->list, FIRST);
    free(popped->data);
    free(popped);
}

void push_stack(struct stack_t  *stack, void *new_data) {
    ll_add_nth_node(stack->list, FIRST, new_data);
}

void clear_stack(struct stack_t  *stack) {
    
    while (stack->list->size) {
        ll_node_t *removed = ll_remove_nth_node(stack->list, FIRST);
        free(removed->data);
        free(removed);
    }
}

void purge_stack(struct stack_t  *stack) {
    ll_free(&stack->list);
}