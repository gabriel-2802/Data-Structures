#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "stack.h"
#include "queue.h"
#include "utils.h"

#define MAX_NODES 500
#define BUF_SIZ 512

typedef struct b_node_t b_node_t;
struct b_node_t
{
    /* left child */
    b_node_t *left;
    /* right child */
    b_node_t *right;

    /* data contained by the node */
    void *data;
};

typedef struct b_tree_t b_tree_t;
struct b_tree_t
{
    /* root of the tree */
    b_node_t *root;

    /* size of the data contained by the nodes */
    size_t data_size;
};

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */ 
static b_node_t *b_node_create(void *data, size_t data_size);

b_tree_t *b_tree_create(size_t data_size);

/**
 * Insert data based on a width traversal, using the first available child
 * (left to right).
 * The current skel uses an iterative solution based on a queue, if you want to
 * use a recursive approach, feel free to create a helper function.
 */
void b_tree_insert(b_tree_t *b_tree, void *data);

/**
 * Print data using a preorder traversal.
 * @b_node: root node with left and right children on which the function is
 * applied recursively
 * @print_data: generic function used to print data
 */
void b_tree_print_preorder(b_node_t *b_node, void (*print_data)(void *));

/**
 * Print data using an inorder traversal.
 * @b_node: root node with left and right children on which the function is
 * applied recursively
 * @print_data: generic function used to print data
 */
void b_tree_print_inorder(b_node_t *b_node, void (*print_data)(void *));

/**
 * Print data using a postorder traversal.
 * @b_node: root node with left and right children on which the function is
 * applied recursively
 * @print_data: generic function used to print data
 */
void b_tree_print_postorder(b_node_t *b_node, void (*print_data)(void *));

/**
 * Free the left and the right subtree of a node, its data and itself.
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void b_tree_free(b_node_t *b_node, void (*free_data)(void *));

void free_b_tree(b_tree_t *b_tree, void (*free_data)(void *));

void print_data(void *data) ;

