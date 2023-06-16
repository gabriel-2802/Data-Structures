#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "ll_lists.h"

#define FIRST 0
#define MAX_STRING_SIZE 64

typedef struct stack_t stack_t;
struct stack_t  {
    ll_list_t *list;
};

void init_stack(struct stack_t  *stack, unsigned int data_size);

int get_size_stack(struct stack_t  *stack);

int is_empty_stack(struct stack_t  *stack);

void* peek_stack(struct stack_t  *stack) ;

void pop_stack(struct stack_t  *stack);

void push_stack(struct stack_t  *stack, void *new_data);

void clear_stack(struct stack_t  *stack);

void purge_stack(struct stack_t  *stack) ;