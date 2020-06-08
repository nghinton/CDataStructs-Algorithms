#ifndef __DA_INCLUDED__
#define __DA_INCLUDED__

#include <stdio.h>

typedef struct DA{

	int size;
	int capacity;
	void **array;

} DA;

extern DA	*newDA(void);
extern void	insertDA(DA *items,int index,void *value);
extern void	*removeDA(DA *items,int index);
extern void	*getDA(DA *items,int index);
extern void	*setDA(DA *items,int index,void *value);
extern int	sizeDA(DA *items);
extern void	freeDA(DA *items);

#define insertDAback(items,value)	insertDA(items,sizeDA(items),value)
#define removeDAback(items)		removeDA(items,sizeDA(items)-1)

#endif
