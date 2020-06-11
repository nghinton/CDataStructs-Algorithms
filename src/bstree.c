#include "dbg.h"
#include "bstree.h"
#include <stdlib.h>
#include "bstrlib.h"

static int default_compare(void *a, void *b)
{
    return bstrcmp((bstring) a, (bstring) b);
}

BST *createBST(compareBST compare)
{
    BST *tree = calloc(1, sizeof(BST));
    check_mem(tree);

    tree->compare = compare == NULL ? default_compare : compare;

    return tree;

error:
    if (tree) {
        destroyBST(tree);
    }
    return NULL;
}

static int BSTree_destroy_cb(BSTnode *node)
{
    free(node);
    return 0;
}

void destroyBST(BST *tree)
{
    if (tree) {
        traverseBST(tree, BSTree_destroy_cb);
        free(tree);
    }
}

static inline BSTnode *createBSTnode(BSTnode *parent, void *key, void *data)
{
    BSTnode *node = calloc(1, sizeof(BSTnode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->parent = parent;
    return node;

error:
    return NULL;
}

static inline void setBSTnode(BST *tree, BSTnode *node, void *key, void *data)
{
    int cmp = tree->compare(node->key, key);

    if (cmp <= 0) {
        if (node->left) {
            setBSTnode(tree, node->left, key, data);
        } else {
            node->left = createBSTnode(node, key, data);
        }
    } else {
        if (node->right) {
            setBSTnode(tree, node->right, key, data);
        } else {
            node->right = createBSTnode(node, key, data);
        }
    }
}

int setBST(BST *tree, void *key, void *data)
{
    if (tree->root == NULL) {
        // first so just make it and get out
        tree->root = createBSTnode(NULL, key, data);
        check_mem(tree->root);
    } else {
        setBSTnode(tree, tree->root, key, data);
    }

    return 0;
error:
    return -1;
}

static inline BSTnode *getBSTnode(BST *tree, BSTnode *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        if (node->left) {
            return getBSTnode(tree, node->left, key);
        } else {
            return NULL;
        }
    } else {
        if (node->right) {
            return getBSTnode(tree, node->right, key);
        } else {
            return NULL;
        }
    }
}

void *getBST(BST *tree, void *key)
{
    if (tree->root == NULL) {
        return NULL;
    } else {
        BSTnode *node = getBSTnode(tree, tree->root, key);
        return node == NULL ? NULL : node->data;
    }
}

static inline int traverseBSTnode(BSTnode * node, BST_traverse_cb traverse_cb)
{
    int rc = 0;

    if (node->left) {
        rc = traverseBSTnode(node->left, traverse_cb);
        if (rc != 0)
            return rc;
    }

    if (node->right) {
        rc = traverseBSTnode(node->right, traverse_cb);
        if (rc != 0)
            return rc;
    }

    return traverse_cb(node);
}

int traverseBST(BST *tree, BST_traverse_cb traverse_cb)
{
    if (tree->root) {
        return traverseBSTnode(tree->root, traverse_cb);
    }

    return 0;
}

static inline BSTnode *findMinBST(BSTnode *node)
{
    while (node->left) {
        node = node->left;
    }

    return node;
}

static inline void BSTree_replace_node_in_parent(BST *tree, BSTnode * node, BSTnode * new_value)
{
    if (node->parent) {
        if (node == node->parent->left) {
            node->parent->left = new_value;
        } else {
            node->parent->right = new_value;
        }
    } else {
        // this is the root so gotta change it
        tree->root = new_value;
    }

    if (new_value) {
        new_value->parent = node->parent;
    }
}

static inline void swapNodeBST(BSTnode *a, BSTnode *b)
{
    void *temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;
    temp = b->data;
    b->data = a->data;
    a->data = temp;
}

static inline BSTnode *removeBSTnode(BST *tree, BSTnode *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp < 0) {
        if (node->left) {
            return removeBSTnode(tree, node->left, key);
        } else {
            // not found
            return NULL;
        }
    } else if (cmp > 0) {
        if (node->right) {
            return removeBSTnode(tree, node->right, key);
        } else {
            // not found
            return NULL;
        }
    } else {
        if (node->left && node->right) {
            // swap this node for the smallest node that is bigger than us
            BSTnode *successor = findMinBST(node->right);
            swapNodeBST(successor, node);

            // this leaves the old successor with possibly a right child
            // so replace it with that right child
            BSTree_replace_node_in_parent(tree, successor,
                    successor->right);

            // finally it's swapped, so return successor instead of node
            return successor;
        } else if (node->left) {
            BSTree_replace_node_in_parent(tree, node, node->left);
        } else if (node->right) {
            BSTree_replace_node_in_parent(tree, node, node->right);
        } else {
            BSTree_replace_node_in_parent(tree, node, NULL);
        }

        return node;
    }
}

void *removeBST(BST *map, void *key)
{
    void *data = NULL;

    if (map->root) {
        BSTnode *node = removeBSTnode(map, map->root, key);

        if (node) {
            data = node->data;
            free(node);
        }
    }

    return data;
}