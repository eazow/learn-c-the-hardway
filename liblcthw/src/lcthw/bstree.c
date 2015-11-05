#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a, void *b)
{
	return bstrcmp((bstring)a, (bstring)b);
}

BSTree *bstree_create(bstree_compare compare)
{
	BSTree *tree = calloc(1, sizeof(BSTree));
	check_mem(tree);

	tree->compare = compare==NULL?default_compare:compare;

	return tree;

error:
	if(tree) {
		bstree_destroy(tree);
	}
	return NULL;
}

static int bstree_destroy_cb(BSTreeNode *node)
{
	free(node);
	return 0;
}

void bstree_destroy(BSTree *tree)
{
	if(tree) {
		bstree_traverse(tree, bstree_destroy_cb);
		free(tree);
	}
}

static inline BSTreeNode *bstree_node_create(BSTreeNode *parent, void *key, void *data)
{
	BSTreeNode *node = calloc(1, sizeof(BSTreeNode));
	check_mem(node);

	node->key = key;
	node->data = data;
	node->parent = parent;
	return node;

error:
	return NULL;
}

static inline void bstree_setnode(BSTree *tree, BSTreeNode *node, void *key, void *data)
{
	int cmp = tree->compare(node->key, key);

	if(cmp < 0) {
		if(node->left) {
			bstree_setnode(tree, node->left, key, data);
		}
		else {
			node->left = bstree_node_create(node, key, data);
		}
	}
	else {
		if(node->right) {
			bstree_setnode(tree, node->right, key, data);
		}
		else {
			node->right = bstree_node_create(node, key, data);
		}
	}
}

int bstree_set(BSTree *tree, void *key, void *data)
{
	if(tree->root == NULL) {
		tree->root = bstree_node_create(NULL, key, data);
		check_mem(tree->root);
	}
	else {
		bstree_setnode(tree, tree->root, key, data);
	}

	return 0;
error:
	return -1;
}

static inline BSTreeNode *bstree_get_node(BSTree *tree, BSTreeNode *node, void *key)
{
	int cmp = tree->compare(node->key, key);

	if(cmp == 0) {
		return node;
	}
	else if(cmp < 0) {
		if(node->left) {
			return bstree_get_node(tree, node->left, key);
		}
		else {
			return NULL;
		}
	}
	else {
		if(node->right) {
			return bstree_get_node(tree, node->right, key);
		}
		else {
			return NULL;
		}
	}
}

void *bstree_get(BSTree *tree, void *key)
{
	if(tree->root == NULL) {
		return NULL;
	}
	else {
		BSTreeNode *node = bstree_get_node(tree, tree->root, key);
		return node == NULL ? NULL : node->data;
	}
}

static inline int bstree_traverse_nodes(BSTreeNode *node, bstree_traverse_cb traverse_cb)
{
	int rc = 0;

	if(node->left) {
		rc = bstree_traverse_nodes(node->left, traverse_cb);
		if(rc != 0) {
			return rc;
		}
	}

	if(node->right) {
		rc = bstree_traverse_nodes(node->right, traverse_cb);
		if(rc != 0) {
			return rc;
		}
	}

	return traverse_cb(node);
}

int bstree_traverse(BSTree *tree, bstree_traverse_cb traverse_cb)
{
	if(tree->root) {
		return bstree_traverse_nodes(tree->root, traverse_cb);
	}

	return 0;
}

static inline BSTreeNode *bstree_find_min(BSTreeNode *node)
{
	while(node->left) {
		node = node->left;
	}

	return node;
}

static inline void bstree_replace_node_in_parent(BSTree *tree, BSTreeNode *node, BSTreeNode *new_node)
{
	if(node->parent) {
		if(node == node->parent->left) {
			node->parent->left = new_node;
		}
		else {
			node->parent->right = new_node;
		}
	}
	else {
		tree->root = new_node;
	}

	if(new_node) {
		new_node->parent = node->parent;
	}
}

static inline void bstree_swap(BSTreeNode *a, BSTreeNode *b)
{
	void *temp = NULL;
	temp = b->key; b->key = a->key; a->key = temp;
	temp = b->data; b->data = a->data; a->data = temp;
}

static inline BSTreeNode *bstree_node_delete(BSTree *tree, BSTreeNode *node, void *key)
{
	int cmp = tree->compare(node->key, key);

	if(cmp < 0) {
		if(node->left) {
			return bstree_node_delete(tree, node->left, key);
		}
		else {
			return NULL;
		}
	}
	else if(cmp > 0) {
		if(node->right) {
			return bstree_node_delete(tree, node->right, key);
		}
		else {
			return NULL;
		}
	}
	else {
		if(node->left && node->right) {
			//swap this node for the smallest node that is bigger tha us
			BSTreeNode *successor = bstree_find_min(node->right);
			bstree_swap(successor, node);

			bstree_replace_node_in_parent(tree, successor, successor->right);

			return successor;
		}
		else if(node->left) {
			bstree_replace_node_in_parent(tree, node, node->left);
		}
		else if(node->right) {
			bstree_replace_node_in_parent(tree, node, node->right);
		}
		else {
			bstree_replace_node_in_parent(tree, node, NULL);
		}

		return node;
	}
}

void *bstree_delete(BSTree *tree, void *key)
{
	void *data = NULL;

	if(tree->root) {
		BSTreeNode *node = bstree_node_delete(tree, tree->root, key);

		if(node) {
			data = node->data;
			free(node);
		}
	}

	return data;
}
