#ifndef _rbtree_h
#define _rbtree_h

typedef int (*compareRBT) (void *a, void *b);

typedef struct RBTnode {
    void *key;
    void *data;

    int color;              // 0 = black, 1 = red

    struct RBTnode *parent;
    struct RBTnode *right;
    struct RBTnode *left;
} RBTnode;

typedef struct RBT {
    int count;
    compareRBT compare;
    RBTnode *root;
} RBT;

typedef int (*RBT_traverse_cb) (RBTnode *node);

RBT *createRBT(compareRBT);
void destroyRBT(RBT *tree);

int insertRBT(RBT *tree, void *key, void *data);
void *removeRBT(RBT *tree, void *key);

void setRBT(RBT *tree, void *key, void *data);
void *getRBT(RBT *tree, void *key);

int traverseRBT(RBT *tree, RBT_traverse_cb traverse_cb);

#endif