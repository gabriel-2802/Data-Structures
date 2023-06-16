#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "BST.h"

static bst_node_t *__bst_node_create(void *data, size_t data_size)
{
	bst_node_t *bst_node;  

	bst_node = malloc(sizeof(*bst_node));

	DIE(bst_node == NULL, "bst_node malloc");

	bst_node->left = bst_node->right = NULL;

	bst_node->data = malloc(data_size);
	DIE(bst_node->data == NULL, "bst_node->data malloc");
	memcpy(bst_node->data, data, data_size);

	return bst_node;
}

bst_tree_t *bst_tree_create(size_t data_size,
	int (*cmp_f)(const void *, const void *))
{
	bst_tree_t *bst_tree;

	bst_tree = malloc(sizeof(*bst_tree));
	DIE(bst_tree == NULL, "bst_tree malloc");

	bst_tree->root  = NULL;
	bst_tree->data_size = data_size;
	bst_tree->cmp   = cmp_f;

	return bst_tree;
}

bst_node_t* insert_node(bst_node_t *node, bst_tree_t *tree, bst_node_t *root)
{
    if (!root)
        return node;
    
    int res = tree->cmp(node->data, root->data);
    if (res < 0)
        root->left = insert_node(node, tree, root->left);
    else
        root->right  = insert_node(node, tree, root->right);
    
    return root;
}

void bst_tree_insert(bst_tree_t *bst_tree, void *data)
{
	int rc;
	bst_node_t *root	= bst_tree->root;
	bst_node_t *parent	= NULL;
	bst_node_t *node	= __bst_node_create(data, bst_tree->data_size);

	bst_tree->root = insert_node(node, bst_tree, root);
    

}


bst_node_t *min_node(bst_node_t *root)
{
    bst_node_t *cur = root;

    while (cur && cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
	void *data, size_t data_size,
	int (*cmp)(const void *, const void *))
{
	int rc;

	if (!bst_node)
		return NULL;

	rc = cmp(data, bst_node->data);

	if (rc < 0) {
		bst_node->left = __bst_tree_remove(bst_node->left, data, data_size, cmp);
	} else if (rc > 0) {
		bst_node->right = __bst_tree_remove(bst_node->right, data, data_size, cmp);
	} else {
		if (!bst_node->left) {
			bst_node_t *temp = bst_node->right;
			free(bst_node->data);
			free(bst_node);
			return temp;
		}
		else if (!bst_node->right) {
			bst_node_t *temp = bst_node->left;
			free(bst_node->data);
			free(bst_node);
			return temp;
		}

		bst_node_t *minimum = min_node(bst_node->right);

		memcpy(bst_node->data, minimum->data, data_size);

		bst_node->right = __bst_tree_remove(bst_node->right, minimum->data, data_size, cmp);
	}

 	return bst_node;
}

void bst_tree_remove(bst_tree_t *bst_tree, void *data)
{
	bst_tree->root = __bst_tree_remove(bst_tree->root, data,
		bst_tree->data_size, bst_tree->cmp);
    

}

static void __bst_tree_free(bst_node_t *bst_node, void (*free_data)(void *))
{
	if (!bst_node)
		return;
    
	__bst_tree_free(bst_node->left, free_data);
    __bst_tree_free(bst_node->right, free_data);

    free_data(bst_node->data);
    free(bst_node);

}

void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *))
{
	__bst_tree_free(bst_tree->root, free_data);
	free(bst_tree);
}
