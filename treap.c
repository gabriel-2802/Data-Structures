#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include "treap.h"

int compare(void* value1, void* value2)
{ 

    int *a = (int*)value1; 
    int *b = (int*)value2;
    if ((*a) > (*b)) {
        return 1; 
    } else if ((*a) < (*b)) {
        return -1; 
    }
    return 0;
}

// Creeaza structura Treap-ului
treap* treap_create(int (*cmp)(void*, void*))
{
	srand(time(NULL));
	treap *tree = malloc(sizeof(treap));
	tree->compare = cmp;
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	return tree;
}
void node_free(treap_node **node)
{

	if (!(*node)) {
		return;
	}
	node_free(&(*node)->left);
	node_free(&(*node)->right);

	free((*node)->data);
	free(*node);
}

void treap_free(treap *tree) 
{
	if (tree->root != NULL) {
		node_free(&tree->root);
	}
	free(tree);
}

treap_node* node_create(void *value, int data_size) 
{
	treap_node *node = malloc(sizeof(treap_node));
	if (node == NULL) {
		return NULL;
	}
	node->data = malloc(data_size);

	// Copiere octet cu octet din value, in nodul curent.
    for (int i = 0; i < data_size; ++i) {
        *(char *)(node->data + i) = *(char *)(value + i);
    }

    // Nodurile frunze au inaltimea 0.
	node->priority = rand() % MAX_PRIORITY;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int max(int a, int b)
{
	if (a > b) {
		return a;
	}
	return b;
}

int priority(treap_node *node)
{
	if (node == NULL) {
		return -1;
	}
	return node->priority;
}

void rotate_right(treap_node **node)
{
	treap_node *lson = (*node)->left;
    (*node)->left = lson->right;
    lson->right = (*node);
    (*node) = lson;

}
	
void rotate_left(treap_node **node)
{
	treap_node *rson = (*node)->right;
    (*node)->right = rson->left;
    rson->left = (*node);
    (*node) = rson;
}

void treap_insert(treap_node **node, void *value, int data_size, int (*compare)(void*, void*))
{
	// TODO: Inserati recursiv in arbore
    if (!(*node)) {
        *node = node_create(value, data_size);
        return;
    }

    int res = compare(value, (*node)->data);

    if (res <= 0) {
        treap_insert(&(*node)->left, value, data_size, compare);

        if ((*node)->left->priority > (*node)->priority) {
            rotate_right(node);
        }
    } else { 
        treap_insert(&(*node)->right, value, data_size, compare);

        if ((*node)->right->priority > (*node)->priority) {
            rotate_left(node);
        }
    }

	// TODO: Reechilibrare arbore
}

void treap_delete(treap_node** node, void* value, int data_size, int (*compare)(void*, void*))
{
    if (!(*node))
        return;
    
    int res= compare(value, (*node)->data);

    if (res< 0) {
        treap_delete(&(*node)->left, value, data_size, compare);
    } else if (res > 0) {
        treap_delete(&(*node)->right, value, data_size, compare);
    } else if (!(*node)->left && !(*node)->right) {
        node_free(node);
        *node = NULL;
    } else if (!(*node)->left) {
        treap_node *curr = *node;
        *node = (*node)->right;

        free(curr->data);
        free(curr);
    } else if (!(*node)->right) {
        treap_node *curr = *node;
        *node = (*node)->left;

        free(curr->data);
        free(curr);
    } else if ((*node)->left->priority > (*node)->right->priority) {
        rotate_right(node);
        treap_delete(node, value, data_size, compare);
    } else {
        rotate_left(node);
        treap_delete(node, value, data_size, compare);
    }
}

void* get_key(treap_node *node, void *value, int data_size, int (*compare)(void*, void*))
{
	if (!node)
        return NULL;
    
    int res = compare(value, node->data);

    if (!res)
        return node->data;

    if (res <= 0)
        return get_key(node->left, value, data_size, compare);
    else if (res > 0)
        return get_key(node->right, value, data_size, compare);
    
}
