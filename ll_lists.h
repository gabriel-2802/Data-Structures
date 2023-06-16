/* copyright Carauleanu Valentin Gabriel 311Cab 2023 */
#pragma once
#include "ll_lists.h"
#include "utils.h"
#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct ll_node_t
{
	void* data;
	struct ll_node_t* next;
} ll_node_t;

typedef struct ll_list_t
{
	ll_node_t* head;
	unsigned int data_size;
	unsigned int size;
} ll_list_t;

/* functia creaza noua lista si initializeaza head cu NULL*/
ll_list_t *ll_create(unsigned int data_size);

/* functia returneaza nodul n din lista */
ll_node_t* get_nth_node(ll_list_t* list, unsigned int n);

/* functia adauga un nou nod pe pozitia n */
void ll_add_nth_node(ll_list_t* list, unsigned int n, const void* new_data);

/* functia sterge nodul n din lista; NU il elibereaza din memorie*/
ll_node_t *ll_remove_nth_node(ll_list_t* list, unsigned int n);

/* functia returneaza marimea listei */
unsigned int ll_get_size(ll_list_t* list);

/* functia elibereaza memoria alocata listei si o reinitializeaza cu NULL */
void ll_free(ll_list_t** pp_list);

void ll_print_int(ll_list_t* list);

void ll_print_string(ll_list_t* list);
