#ifndef __CDA_INCLUDED__
#define __CDA_INCLUDED__

#include <stdio.h>

typedef struct CDA{
	int front;
	int back;
	int size;
	int capacity;
	void **array;	
} CDA;

extern CDA	*newCDA(void);
extern void	insertCDA(CDA *items,int index,void *value);
extern void	*removeCDA(CDA *items,int index);
extern void	*getCDA(CDA *items,int index);
extern void	*setCDA(CDA *items,int index, void *value);
extern int	sizeCDA(CDA *items);
extern void	freeCDA(CDA *items);

#define insertCDAfront(items,value)	insertCDA(items,0,value)
#define insertCDAback(items, value)	insertCDA(items, sizeCDA(items),value)
#define removeCDAfront(items)		removeCDA(items, 0)
#define removeCDAback(items)		removeCDA(items,sizeCDA(items)-1)

#endif
