#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll_lists.h"
#include "utils.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX_STRING_SIZE	256

/* Graful este ORIENTAT */

typedef struct
{
	ll_list_t** neighbors; /* Listele de adiacenta ale grafului */
	int nodes;                 /* Numarul de noduri din graf. */
} list_graph_t;

/* Adauga o muchie intre nodurile primite ca parametri */
void lg_add_edge(list_graph_t* graph, int src, int dest);

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int lg_has_edge(list_graph_t* graph, int src, int dest);

/* Elimina muchia dintre nodurile primite ca parametri */
void lg_remove_edge(list_graph_t* graph, int src, int dest);

/* Elibereaza memoria folosita de lista de adiacenta a grafului */
void lg_free(list_graph_t* graph);

/* Printeaza lista de adiacenta a grafului
 */
void lg_print_graph(list_graph_t* graph);

