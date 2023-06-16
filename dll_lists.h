#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"                            
    
typedef struct dll_node_t dll_node_t;

struct dll_node_t {
	void *data;
	/* Pentru ca datele stocate sa poata avea orice tip, folosim un
	pointer la void. */
	dll_node_t *prev, *next;
};

typedef struct dll_list_t dll_list_t;

struct dll_list_t {
	dll_node_t *head;
	unsigned int data_size;
	unsigned int size;
};

dll_list_t *dll_create(unsigned int data_size);

dll_node_t *dll_get_nth_node(dll_list_t *list, unsigned int n);

void dll_add_nth_node(dll_list_t *list, unsigned int n, const void *new_data);

dll_node_t *dll_remove_nth_node(dll_list_t *list, unsigned int n);

void dll_free(dll_list_t **pp_list);

