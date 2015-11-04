#ifndef _lcthw_bstree_h
#define _lcthw_bstree_h

typedef int (*bstree_compare)(void *a, void *b);

typedef struct BSTreeNode {
	void *key;
	void *data;

	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
} BSTreeNode;

typedef struct BSTree {
	int count;
	bstree_compare compare;
	BSTreeNode *root;
} BSTree;

typedef int (*bstree_traverse_cb)(BSTreeNode *node);

BSTree *bstree_create(bstree_compare compare);
void bstree_destroy(BSTree *tree);

int bstree_set(BSTree *tree, void *key, void *data);
void *bstree_get(BSTree *tree, void *key);

int bstree_traverse(BSTree *tree, bstree_traverse_cb traverse_cb);

void *bstree_delete(BSTree *tree, void *key);

#endif
