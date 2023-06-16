#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

typedef struct bst_node_t bst_node_t;
struct  bst_node_t {
	/* left child */
	bst_node_t *left;

	/* right child */
	bst_node_t *right;

	/* data contained by the node */
	void *data;
};

typedef struct bst_tree_t bst_tree_t;
struct bst_tree_t {
	/* root of the tree */
	bst_node_t  *root;

	 /* size of the data contained by the nodes */
	size_t data_size;

	/* function used for sorting the keys */
	int	(*cmp)(const void *key1, const void *key2);
};

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static bst_node_t *__bst_node_create(void *data, size_t data_size);

/**
 * Alloc memory for a new BST
 * @data_size: size of the data contained by the BST's nodes
 * @cmp_f: pointer to a function used for sorting
 * @return: pointer to the newly created BST
 */
bst_tree_t *bst_tree_create(size_t data_size,
	int (*cmp_f)(const void *, const void *));

/**
 * Insert a new element in a BST
 * @bst_tree: the BST where to insert the new element
 * @data: the data to be inserted in BST
 */

bst_node_t* insert_node(bst_node_t *node, bst_tree_t *tree, bst_node_t *root);


void bst_tree_insert(bst_tree_t *bst_tree, void *data);

bst_node_t *min_node(bst_node_t *root);

/**
 * Helper function to remove an element from a BST
 * @bst_node: the binary search subtree's root where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 * @data_size: data size
 * @cmp: function used to compare the data contained by two nodes
 */
static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
	void *data, size_t data_size,
	int (*cmp)(const void *, const void *));

/**
 * Remove an element from a BST
 * @bst_tree: the BST where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 */
void bst_tree_remove(bst_tree_t *bst_tree, void *data);

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void __bst_tree_free(bst_node_t *bst_node, void (*free_data)(void *));

/**
 * Free a BST
 * @bst_tree: the BST to be freed
 * @free_data: function used to free the data contained by a node
 */
void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *));