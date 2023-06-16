#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include "matrix_graphs.h"

/* Graful este ORIENTAT */

matrix_graph_t *mg_create(int nodes)
{
    
    matrix_graph_t *graph = malloc(sizeof(matrix_graph_t));
    DIE(!graph, "malloc\n");

    graph->matrix = malloc(sizeof(int *) * nodes);
    DIE(!graph->matrix, "malloc\n");

    for (int i = 0; i < nodes; ++i) {
        graph->matrix[i] = calloc(nodes, sizeof(int));
        DIE(!graph->matrix[i], "malloc\n");
    }
    
    graph->nodes = nodes;
    return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void mg_add_edge(matrix_graph_t* graph, int src, int dest)
{
    graph->matrix[src][dest] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int mg_has_edge(matrix_graph_t* graph, int src, int dest)
{
    if (graph->matrix[src][dest])
        return 1;
    
    return 0;
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void mg_remove_edge(matrix_graph_t* graph, int src, int dest)
{
    graph->matrix[src][dest] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void mg_free(matrix_graph_t* graph)
{
    for (int i = 0; i < graph->nodes; ++i)
        free(graph->matrix[i]);

    free(graph->matrix);
    free(graph);
}

void print_matrix_graph(matrix_graph_t* mg)
{
    for (int i = 0; i < mg->nodes; ++i) {

        for (int j = 0; j < mg->nodes; ++j)
            printf("%d ", mg->matrix[i][j]);
        printf("\n");
    }
}

void floydWarshall(matrix_graph_t* mg)
{
    int **dist = malloc(sizeof(int *) * mg->nodes);
    DIE(!dist, "malloc\n");
    for (int i = 0; i < mg->nodes; ++i) {
        dist[i] = malloc(sizeof(int) * mg->nodes);
        DIE(!dist[i], "malloc\n");
    }

    for (int i = 0; i < mg->nodes; ++i)
        for (int j = 0; j < mg->nodes; ++j)
            dist[i][j] = INF;
    
    for (int i = 0; i < mg->nodes; ++i)
        for (int j = 0; j < mg->nodes; ++j)
            if (mg->matrix[i][j] == 1)
                dist[i][j] = 1;
    
    for (int k = 0; k < mg->nodes; ++k)
        for (int i = 0; i < mg->nodes; ++i)
            for (int j = 0; j < mg->nodes; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    for (int i = 0; i < mg->nodes; ++i) {
        for (int j = 0; j < mg->nodes; ++j)
            if (dist[i][j] == INF)
                dist[i][j] = -1;
    }

    for (int i = 0; i < mg->nodes; ++i) {
        for (int j = 0; j < mg->nodes; ++j)
            printf("%d ", dist[i][j]);
        printf("\n");
    }

    for (int i = 0; i < mg->nodes; ++i)
        free(dist[i]);
    free(dist);
}