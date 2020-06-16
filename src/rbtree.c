#include "dbg.h"
#include "rbtree.h"
#include "bstrlib.h"
#include <stdlib.h>
#include <assert.h>

/* Standard creation and deletion functions
 *      createRBT()
 *      destroyRBT()
 *      default_comparison()
 */

static int default_compare(void *a, void *b)
{
    return bstrcmp((bstring) a, (bstring) b);
}

RBT *createRBT(compareRBT compare)
{
    RBT *tree = calloc(1, sizeof(RBT));
    check_mem(tree);

    tree->compare = compare == NULL ? default_compare : compare;

    return tree;

error:
    if (tree) {
        destroyRBT(tree);
    }
    return NULL;
}

static int RBTree_destroy_cb(RBTnode *node)
{
    free(node);
    return 0;
}

void destroyRBT(RBT *tree)
{
    if (tree) {
        traverseRBT(tree, RBTree_destroy_cb);
        free(tree);
    }
}

/* Helper Functions
 *      swapRBT()
 *      GetParent()
 *      GetGranparent()
 *      GetSibling()
 *      GetUncle()
 *      RightRotate()
 *      LeftRotate()
 */

static inline void swapRBT(RBTnode *a, RBTnode *b)
{
    void *temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;
    temp = b->data;
    b->data = a->data;
    a->data = temp;
}

RBTnode *GetParent(RBTnode *node) 
{
  // Note that parent is set to null for the root node.
  return node == NULL ? NULL : node->parent;
}

RBTnode* GetGrandParent(RBTnode* node) 
{
  // Note that it will return nullptr if this is root or child of root
  return GetParent(GetParent(node));
}

RBTnode *GetSibling(RBTnode *node) 
{
  RBTnode *parent = GetParent(node);

  // No parent means no sibling.
  if (parent == NULL) {
    return NULL;
  }

  if (node == parent->left) 
  {
    return parent->right;
  } else {
    return parent->left;
  }
}

RBTnode *GetUncle(RBTnode *node) 
{
  RBTnode* parent = GetParent(node);

  // No parent means no uncle
  return GetSibling(parent);
}

void RotateLeft(RBTnode *node) 
{
  RBTnode* new = node->right;
  RBTnode* parent = GetParent(node);
  assert(new != NULL);  // Since the leaves of a red-black tree are empty,
                            // they cannot become internal nodes.
  node->right = new->left;
  new->left = node;
  node->parent = new;
  // Handle other child/parent pointers.
  if (node->right != NULL) {
    node->right->parent = node;
  }
  // Initially n could be the root.
  if (parent != NULL) {
    if (node == parent->left) {
      parent->left = new;
    } else if (node == parent->right) {
      parent->right = new;
    }
  }
  new->parent = parent;
}

void RotateRight(RBTnode *node)
{
  RBTnode *new = node->left;
  RBTnode* parent = GetParent(node);
  assert(new != NULL);  // Since the leaves of a red-black tree are empty,
                            // they cannot become internal nodes.

  node->left = new->right;
  new->right = node;
  node->parent = new;
  // Handle other child/parent pointers.
  if (node->left != NULL) {
    node->left->parent = node;
  }
  // Initially n could be the root.
  if (parent != NULL) {
    if (node == parent->left) {
      parent->left = new;
    } else if (node == parent->right) {
      parent->right = new;
    }
  }
  new->parent = parent;
}

/* Insertion and its helping functions
 *      insertRBT()
 *      insertRBThelper()
 *      insertRBTFix()
 *      newRBTnode()
 */

RBTnode *newRBTnode(void *key, void *data) 
{
    RBTnode *new = calloc(1, sizeof(RBTnode));
    assert(new != NULL);

    new->key = key;
    new->data = data;
    new->color = 1;         // 1 for red, all new nodes begin red

    return new;
}

void insertRBThelper(RBT *tree, RBTnode *node, RBTnode *new)
{
    int cmp = tree->compare(node->key, new->key);

    if (cmp <= 0) {
        if (node->left) {
            insertRBThelper(tree, node->left, new);
        } else {
            node->left = new;
            new->parent = node;
        }
    } else {
        if (node->right) {
            insertRBThelper(tree, node->right, new);
        } else {
            node->right = new;
            new->parent = node;
        }
    }
}

void insertRBTfix(RBTnode *node) 
{
    if (GetParent(node) == NULL) {
        node->color = 0;
    } else if (GetParent(node)->color == 0) {
        // Do nothing
    } else if (GetUncle(node) != NULL && GetUncle(node)->color == 1) {
        GetParent(node)->color = 0;
        GetUncle(node)->color = 0;
        GetGrandParent(node)->color = 1;
        insertRBTfix(GetGrandParent(node));
    }  else {
        RBTnode* parent = GetParent(node);
        RBTnode* grandparent = GetGrandParent(node);

        if (grandparent != NULL) {
            if (node == parent->right && parent == grandparent->left) {
               RotateLeft(parent);
                node = node->left;
            } else if (node == parent->left && parent == grandparent->right) {
                RotateRight(parent);
                node = node->right;
            }
        }

        // Reset parent and granparent
        parent = GetParent(node);
        grandparent = GetGrandParent(node);
        if (grandparent != NULL) {
            if (node == parent->left) {
                RotateRight(grandparent);
            } else {
                RotateLeft(grandparent);
            }
        }
        

        parent->color = 0;
        if (grandparent != NULL) {
            grandparent->color = 1;
        }
    }

}

int insertRBT(RBT *tree, void *key, void *data) 
{
    // Create the new node
    RBTnode *new = newRBTnode(key, data);

    // See if this is the first node, otherwise 
    // insert like normal
    if (tree->root == NULL) {
        tree->root = new;
        tree->count++;
        return 0;
    } else {
        insertRBThelper(tree, tree->root, new);
    }

    // Call fix to ensure RB properties remain true
    insertRBTfix(new);

    // Find the new root just in case
    RBTnode *root = new;
    while (GetParent(root) != NULL) {
        root = GetParent(root);
    }
    tree->root = root;

    // Update tree count
    tree->count++;

    return 0;

}

/* Removal and its helping functions
 *      removeRBT()
 *      removeRBThelper()
 *      findMinRBT()
 *      replaceParentRBT()
 *      removeRBTFix()
 */

static inline RBTnode *findMinRBT(RBTnode *node)
{
    while (node->left) {
        node = node->left;
    }
    return node;
}

void removalRBTfix(RBT *tree, RBTnode *node) 
{
    if (GetParent(node)) {
        if (GetSibling(node)) {
           if (GetSibling(node)->color == 1) {
                GetParent(node)->color = 1;
                GetSibling(node)->color = 0;
                if (node == GetParent(node)->left) {
                    RotateLeft(GetParent(node));
                } else {
                    RotateRight(GetParent(node));
                }
            }
            if ((GetParent(node)->color == 0) && (GetSibling(node)->color == 0)) {
                if ( !GetSibling(node)->left || GetSibling(node)->left->color == 0) {
                    if ( !GetSibling(node)->right || GetSibling(node)->right->color == 0) {
                        GetSibling(node)->color = 1;
                        removalRBTfix(tree, GetParent(node));
                    }
                }  
            } 
            else {
                if (GetSibling(node)) {
                if ((GetParent(node)->color == 1) && (GetSibling(node)->color == 0)) {
                    if ( !GetSibling(node)->left || GetSibling(node)->left->color == 0) {
                        if ( !GetSibling(node)->right || GetSibling(node)->right->color == 0) {
                            GetSibling(node)->color = 1;
                            GetParent(node)->color = 0;
                        }
                    }  
                } 
                }
                else {
                    if (GetSibling(node)) {
                    if (GetSibling(node)->color == 0) {
                        if (node == GetParent(node)->left) {
                            if ( GetSibling(node)->right && GetSibling(node)->right->color == 0) {
                                if ( GetSibling(node)->left || GetSibling(node)->left->color == 1) {
                                    GetSibling(node)->color = 1;
                                    if(GetSibling(node)->left) {
                                        GetSibling(node)->left->color = 0;
                                    }
                                    RotateRight(GetSibling(node));
                                }
                            }  
                        } 
                        else if (node == GetParent(node)->right) {
                            if ( GetSibling(node)->left && GetSibling(node)->left->color == 0) {
                                if ( GetSibling(node)->right || GetSibling(node)->right->color == 1) {
                                    GetSibling(node)->color = 1;
                                    if(GetSibling(node)->right) {
                                        GetSibling(node)->right->color = 0;
                                    }
                                    RotateLeft(GetSibling(node));
                                }
                            }  
                        }
                    }
                    }
                    if (GetSibling(node)) {
                    GetSibling(node)->color = GetParent(node)->color;
                    GetParent(node)->color = 0;
                    if ( node == GetParent(node->left) ) {
                        if ( GetSibling(node)->right ) {
                            GetSibling(node)->right->color = 0;
                            RotateLeft(GetParent(node));
                        } 
                    } else {
                        if ( GetSibling(node)->left ) {
                            GetSibling(node)->left->color = 0;
                            RotateRight(GetParent(node));
                        }
                    }
                    }
                } 
            }
        }
    }
}

static inline void replaceParentRBT(RBT *tree, RBTnode *node, RBTnode *new)
{
    if (node->parent) {
        if (node == node->parent->left) {
            node->parent->left = new;
        } else {
            node->parent->right = new;
        }
    } else {
        // this is the root so gotta change it
        tree->root = new;
    }

    if (new) {
        new->parent = node->parent;
        new->color = 0;             // Have to change this to black (i think)
    }

    // When node is replaced, call removalRBTfix on the successor
    // to maintain RB tree properties (doing it here because doing it in the actual remove is a pain)
    // If node was a red node deleting it doesnt matter. If black call the Fix
    if (node->color == 0) {
        removalRBTfix(tree, new);
    }

}

void *removeRBThelper(RBT *tree, RBTnode *node, void *key) 
{
    int cmp = tree->compare(node->key, key);

    if (cmp < 0) {
        if (node->left) {
            return removeRBThelper(tree, node->left, key);
        } else {
            // not found
            return NULL;
        }
    } else if (cmp > 0) {
        if (node->right) {
            return removeRBThelper(tree, node->right, key);
        } else {
            // not found
            return NULL;
        }
    } else {
        if (node->left && node->right) {
            // swap this node for the smallest node that is bigger than us
            RBTnode *successor = findMinRBT(node->right);
            swapRBT(successor, node);

            // this leaves the old successor with possibly a right child
            // so replace it with that right child
            replaceParentRBT(tree, successor, successor->right);

            // finally it's swapped, so return successor instead of node
            return successor;
        } else if (node->left) {
            replaceParentRBT(tree, node, node->left);
        } else if (node->right) {
            replaceParentRBT(tree, node, node->right);
        } else {
            replaceParentRBT(tree, node, NULL);
        }

        // Finally return the node to be removed
        return node;

    }

}

void *removeRBT(RBT *tree, void *key)
{
    void *data = NULL;

    if (tree->root) {
        RBTnode *node = removeRBThelper(tree, tree->root, key);
        
        if (node) {
            // Copy data to the void pointer to be returned
            data = node->data;
            // Free the node
            free(node);
            // Update tree count
            tree->count--;
        }
    }

    return data;
}

/* Set, Get and other functions
 *      setRBT()
 *      getRBT()
 *      getRBThelper()
 *      traverseRBT()
 *      traverseRBThelper()
 */

void setRBT(RBT *tree, void *key, void *data) 
{
    // Get the node to set from the tree with the 
    // passed in key
    RBTnode *node = getRBT(tree, key);

    // Set the retieved node's data to the new value
    node->data = data;

    return;
}

static inline RBTnode *getRBThelper(RBT *tree, RBTnode *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        if (node->left) {
            return getRBThelper(tree, node->left, key);
        } else {
            return NULL;
        }
    } else {
        if (node->right) {
            return getRBThelper(tree, node->right, key);
        } else {
            return NULL;
        }
    }
}

void *getRBT(RBT *tree, void *key)
{
    if (tree->root == NULL) {
        return NULL;
    } else {
        RBTnode *node = getRBThelper(tree, tree->root, key);
        return node == NULL ? NULL : node->data;
    }
}

static inline int traverseRBThelper(RBTnode * node, RBT_traverse_cb traverse_cb)
{
    int rc = 0;

    if (node->left) {
        rc = traverseRBThelper(node->left, traverse_cb);
        if (rc != 0)
            return rc;
    }

    if (node->right) {
        rc = traverseRBThelper(node->right, traverse_cb);
        if (rc != 0)
            return rc;
    }

    return traverse_cb(node);
}

int traverseRBT(RBT *tree, RBT_traverse_cb traverse_cb)
{
    // Check and make sure the tree has at least one node
    if (tree->root) {
        return traverseRBThelper(tree->root, traverse_cb);
    }

    return 0;
}