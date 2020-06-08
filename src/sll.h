#include <stdlib.h>

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

typedef struct sllnode
    {
    void *value;
    struct sllnode *next;
    } sllnode;

typedef struct sll
    {
    sllnode *head;
    sllnode *tail;
    int size;
    } sll;

extern sll *newSLL();
extern void insertSLL(sll *items,int index,void *value);
extern void *removeSLL(sll *items,int index);
extern void *getSLL(sll *items,int index);  
extern void *setSLL(sll *items, int index,void *value);
extern int sizeSLL(sll *items);
extern void freeSLL(sll *items);

#define insertSLLback(items,value)	insertSLL(items,sizeSLL(items),value)
#define removeSLLback(items)		removeSLL(items,sizeSLL(items)-1)

#endif