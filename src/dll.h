#include <stdlib.h>

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

typedef struct dllnode
    {
    void *value;
    struct dllnode *next;
    struct dllnode *prev;
    } dllnode;

typedef struct dll
    {
    dllnode *head;
    dllnode *tail;
    int size;
    } dll;

extern dll *newDLL();
extern void insertDLL(dll *items,int index,void *value);
extern void *removeDLL(dll *items,int index);
extern void *getDLL(dll *items,int index);  
extern void *setDLL(dll *items, int index,void *value);
extern int sizeDLL(dll *items);
extern void freeDLL(dll *items);

#define insertDLLback(items,value)	insertDLL(items,sizeDLL(items),value)
#define removeDLLback(items)		removeDLL(items,sizeDLL(items)-1)


#endif