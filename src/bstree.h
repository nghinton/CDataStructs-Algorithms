#ifndef _lcthw_BSTree_h
#define _lcthw_BSTree_h

typedef int (*compareBST) (void *a, void *b);

typedef struct BSTnode {
    void *key;
    void *data;

    struct BSTnode *left;
    struct BSTnode *right;
    struct BSTnode *parent;
} BSTnode;

typedef struct BST {
    int count;
    compareBST compare;
    BSTnode *root;
} BST;

typedef int (*BST_traverse_cb) (BSTnode * node);

BST *createBST(compareBST compare);
void destroyBST(BST *tree);

int setBST(BST *tree, void *key, void *data);
void *getBST(BST *tree, void *key);
void *removeBST(BST *tree, void *key);

int traverseBST(BST *tree, BST_traverse_cb traverse_cb);

#endif