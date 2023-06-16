#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "queue.h"

queue_t *q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *q = malloc(sizeof(queue_t));
    DIE(!q, "malloc failed\n");
    
    q->data_size = data_size;
    q->max_size = max_size;
    q->size = 0;
    q->read_idx = 0;
    q->write_idx = 0;

    q->buff = malloc(q->max_size * sizeof(void *));
    DIE(!q->buff, "malloc failed\n");

    return q;
}

/*
 * Functia intoarce numarul de elemente din coada al carei pointer este trimis
 * ca parametru.
 */
unsigned int q_get_size(queue_t *q)
{   
    if (!q)
        return 0;
	return q->size;
}

/*
 * Functia intoarce 1 daca coada este goala si 0 in caz contrar.
 */
unsigned int q_is_empty(queue_t *q)
{
	return (0 == q->size);
}

/* 
 * Functia intoarce primul element din coada, fara sa il elimine.
 */
void *q_front(queue_t *q)
{
	if (!q || !q->size)
        return NULL;
    
    return q->buff[q->read_idx];
    
}

/*
 * Functia scoate un element din coada. Se va intoarce 1 daca operatia s-a
 * efectuat cu succes (exista cel putin un element pentru a fi eliminat) si
 * 0 in caz contrar.
 */
int q_dequeue(queue_t *q)
{
	if (!q || !q->size)
        return 0;
    
    free(q->buff[q->read_idx % q->max_size]);
    q->read_idx++;
    q->size--;

    if (q->read_idx >= q->max_size)
        q->read_idx = 0;
}

/* 
 * Functia introduce un nou element in coada. Se va intoarce 1 daca
 * operatia s-a efectuat cu succes (nu s-a atins dimensiunea maxima) 
 * si 0 in caz contrar.
 */
int q_enqueue(queue_t *q, void *new_data)
{
	if (q->size == q->max_size)
	    return 0;
    
    void *data = malloc(q->data_size);
    DIE(!data, "malloc failed\n");
    memcpy(data, new_data, q->data_size);

    q->buff[q->write_idx % q->max_size] = data;
    q->write_idx++;
    q->size++; 
}

/*
 * Functia elimina toate elementele din coada primita ca parametru.
 */
void q_clear(queue_t *q)
{
	while (q->size)
        q_dequeue(q);
}

/*
 * Functia elibereaza toata memoria ocupata de coada.
 */
void q_free(queue_t *q)
{
	q_clear(q);
    free(q->buff);
    free(q);
}