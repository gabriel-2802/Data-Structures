#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "binarry_tree.h"

static b_node_t *b_node_create(void *data, size_t data_size)
{
    b_node_t *b_node;

    b_node = malloc(sizeof(*b_node));
    DIE(b_node == NULL, "b_node malloc");

    b_node->left = b_node->right = NULL;

    b_node->data = malloc(data_size);
    DIE(b_node->data == NULL, "b_node->data malloc");
    memcpy(b_node->data, data, data_size);

    return b_node;
}

b_tree_t *b_tree_create(size_t data_size)
{
    b_tree_t * tree = malloc(sizeof(b_tree_t));
    DIE(!tree, "malloc\n");

    tree->data_size = data_size;
    tree->root = NULL;
}

void b_tree_insert(b_tree_t *b_tree, void *data)
{
    queue_t *q;
    b_node_t *b_node, *b_node_tmp;
    b_node_t **b_node_tmp_addr;

    b_node = b_node_create(data, b_tree->data_size);

    if (!b_tree->root)
    {
        b_tree->root = b_node;
        return;
    }

    q = q_create(sizeof(b_node_t *), MAX_NODES);
    q_enqueue(q, &b_tree->root);


    while (!q_is_empty(q)) {
        b_node_t *node = *((b_node_t **)q_front(q));
        q_dequeue(q);

        if (!node->left) {
            node->left = b_node;
            break;
        }

        if (!node->right) {
            node->right = b_node;
            break;
        }

        q_enqueue(q, &node->left);
        q_enqueue(q, &node->right);
    }

    q_free(q);
}

void b_tree_print_preorder(b_node_t *b_node, void (*print_data)(void *))
{
    if (!b_node)
        return;

    print_data(b_node->data);
    b_tree_print_preorder(b_node->left, print_data);
    b_tree_print_preorder(b_node->right, print_data);

}

void b_tree_print_inorder(b_node_t *b_node, void (*print_data)(void *))
{
    if (!b_node)
        return;

    b_tree_print_inorder(b_node->left, print_data);
    print_data(b_node->data);
    b_tree_print_inorder(b_node->right, print_data);
}

void b_tree_print_postorder(b_node_t *b_node, void (*print_data)(void *))
{
    if (!b_node)
        return;

    b_tree_print_postorder(b_node->left, print_data);
    b_tree_print_postorder(b_node->right, print_data);
    print_data(b_node->data);
}

/**
 * Free the left and the right subtree of a node, its data and itself.
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void b_tree_free(b_node_t *b_node, void (*free_data)(void *))
{
    if (!b_node)
        return;

    b_tree_free(b_node->left, free_data);
    b_tree_free(b_node->right, free_data);
    free_data(b_node->data);
    free(b_node);
}

void free_b_tree(b_tree_t *b_tree, void (*free_data)(void *))
{
    b_tree_free(b_tree->root, free_data);
    free(b_tree);
}
void print_data(void *data) 
{
    printf("%d ", *(int *)data);
}
