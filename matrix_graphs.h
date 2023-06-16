#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define INF 1000000
#define MAX_STRING_SIZE    256

typedef struct
{
    int** matrix; /* Matricea de adiacenta a grafului */
    int nodes;    /* Numarul de noduri din graf. */
} matrix_graph_t;

matrix_graph_t *mg_create(int nodes);

/* Adauga o muchie intre nodurile sursa si destinatie */
void mg_add_edge(matrix_graph_t* graph, int src, int dest);

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int mg_has_edge(matrix_graph_t* graph, int src, int dest);

/* Elimina muchia dintre nodurile sursa si destinatie */
void mg_remove_edge(matrix_graph_t* graph, int src, int dest);

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void mg_free(matrix_graph_t* graph);

void print_matrix_graph(matrix_graph_t* mg);

void floydWarshall(matrix_graph_t* mg);
