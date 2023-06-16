#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>

#define MAX_NODES 1000
#define MAX_PRIORITY 1000

typedef struct treap_node {
	void *data;
	int priority;

	struct treap_node *left, *right;
} treap_node;

typedef struct {
	treap_node *root;
	int(*compare)(void*, void*);
} treap;

int compare(void* value1, void* value2);

// Creeaza structura Treap-ului
treap* treap_create(int (*cmp)(void*, void*));

void node_free(treap_node **node);

void treap_free(treap *tree) ;

/* Creeaza un nod 
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
treap_node* node_create(void *value, int data_size);

int max(int a, int b);

// Nodurile NULL au prioritatea -1 pentru a pastra proprietatea de max-heap.
int priority(treap_node *node);

/* Rotire dreapta
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *      node  			    lson
 *     /    \			   /    \ 
 *   lson    y    --->    x    node
 *   /  \     		           /   \ 
 *  x   lrson                lrson  y
 */
void rotate_right(treap_node **node);

/* Rotire stanga
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *     node  			    rson
 *    /    \			   /    \ 
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */	
void rotate_left(treap_node **node);

/* Inserare in Treap
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void treap_insert(treap_node **node, void *value, int data_size, int (*compare)(void*, void*));

/* Stergere din Treap
 *
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void treap_delete(treap_node** node, void* value, int data_size, int (*compare)(void*, void*));

void* get_key(treap_node *node, void *value, int data_size, int (*compare)(void*, void*));


