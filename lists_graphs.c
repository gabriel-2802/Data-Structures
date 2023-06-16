#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists_graphs.h"

list_graph_t* lg_create(int nodes)
{
	list_graph_t *graph = malloc(sizeof(list_graph_t));
    DIE(!graph, "malloc\n");

    graph->neighbors = malloc(nodes * sizeof(ll_list_t*));
    DIE(!graph->neighbors, "malloc\n");

    graph->nodes = nodes;
    for (int i = 0; i  < nodes; ++i)
        graph->neighbors[i] = ll_create(sizeof(int));
    
    return graph;

}

/* Adauga o muchie intre nodurile primite ca parametri */
void lg_add_edge(list_graph_t* graph, int src, int dest)
{
	ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
    //ll_add_nth_node(graph->neighbors[dest], graph->neighbors[dest]->size, &src);
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int lg_has_edge(list_graph_t* graph, int src, int dest)
{
    ll_node_t *neigh = graph->neighbors[src]->head;

	for (int i = 0; i < graph->neighbors[src]->size; ++i) {
        if (dest == *(int *)neigh->data)
            return 1;
        neigh = neigh->next;
    }
    return 0;
}

/* Elimina muchia dintre nodurile primite ca parametri */
void lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	ll_node_t *neigh = graph->neighbors[src]->head;
    for (int i = 0; i < graph->neighbors[src]->size; ++i) {
        if (dest == *(int *)neigh->data) {
            ll_remove_nth_node(graph->neighbors[src], i);
            return;
        }
        neigh = neigh->next;
    }

    // neigh = graph->neighbors[dest]->head;
    // for (int i = 0; i < graph->neighbors[dest]->size; ++i) {
    //     if (src == *(int *)neigh->data);
    //     ll_remove_nth_node(graph->neighbors[dest], i);
    // }    
}

/* Elibereaza memoria folosita de lista de adiacenta a grafului */
void lg_free(list_graph_t* graph)
{
	for (int i = 0; i < graph->nodes; ++i)
        ll_free(&graph->neighbors[i]);
    free(graph->neighbors);
    free(graph);
}

/* Printeaza lista de adiacenta a grafului
 */
void lg_print_graph(list_graph_t* graph)
{
	for (int i = 0; i < graph->nodes; ++i) {
        printf("%d: ", i);
        ll_print_int(graph->neighbors[i]);
    }
}
