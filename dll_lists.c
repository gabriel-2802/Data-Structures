#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dll_lists.h"

dll_list_t *dll_create(unsigned int data_size)
{
	dll_list_t *list = malloc(sizeof(dll_list_t));
	DIE(!list, "malloc failed\n");

	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;
	return list;
}

dll_node_t *dll_get_nth_node(dll_list_t *list, unsigned int n)
{
	if (!list || !list->head)
		return NULL;

	n %= list->size;
	/*pt a nu cicla prin lista la un n mai mare
	decat lungimea listei, vom aplica % */

	dll_node_t *cur = list->head;
	for (int i = 0; i < (int)n; ++i)
		cur = cur->next;

	return cur;
}

void dll_add_nth_node(dll_list_t *list, unsigned int n, const void *new_data)
{
	if (!list)
		return;

	if (n >= list->size)
		n = list->size;

	//cream noul nodul
	dll_node_t *new_node = malloc(sizeof(dll_node_t));
	DIE(!new_node, "malloc failed\n");

	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, "malloc failed\n");
	memcpy(new_node->data, new_data, list->data_size);

	/*verificam daca n == 0, pentru a seta head-ul listei la
	noul nod */
	if (!n) {
		if (!list->size) {
			new_node->next = new_node;
			new_node->prev = new_node;
			list->head = new_node;
			list->size++;
			return;
		}

		new_node->next = list->head;
		new_node->prev = list->head->prev;
		list->head->prev->next = new_node;
		list->head->prev = new_node;
		list->head = new_node;
		list->size++;
		return;
	}

	//daca n != 0, parurgem lista pana la positia n - 1
	dll_node_t *cur = list->head;
	for (int i = 0; i < (int)n - 1; ++i)
		cur = cur->next;

	new_node->next = cur->next;
	cur->next->prev = new_node;
	new_node->prev = cur;
	cur->next = new_node;
	list->size++;
}

dll_node_t *dll_remove_nth_node(dll_list_t *list, unsigned int n)
{
	if (!list || !list->head)
		return NULL;

	if (n >= list->size)
		n = list->size - 1;

	dll_node_t *cur = list->head;

	for (int i = 0; i < (int)n; ++i)
		cur = cur->next;

	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	//daca n == 0, modficam head-ul listei
	if (!n)
		list->head = cur->next;

	list->size--;
	//la final returnam nodul eliminat
	return cur;
}

void dll_free(dll_list_t **pp_list)
{
	if (!(*pp_list))
		return;

	if (!(*pp_list)->size) {
		free(*pp_list);
		*pp_list = NULL;
		return;
	}

	dll_node_t *node = (*pp_list)->head;
	//rupem ciclul
	node->prev->next = NULL;

	while (node->next) {
		node = node->next;
		free(node->prev->data);
		free(node->prev);
	}

	free(node->data);
	free(node);
	free((*pp_list));
}