#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

#include <stdio.h>

typedef struct STACK STACK;

extern STACK	*newSTACK(void);
extern void	push(STACK *items,void *value);
extern void	*pop(STACK *items);
extern void	*peekSTACK(STACK *items);
extern void	freeSTACK(STACK *items);
extern int	sizeSTACK(STACK *items);

#endif
