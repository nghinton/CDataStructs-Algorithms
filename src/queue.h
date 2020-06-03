#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>

typedef struct QUEUE QUEUE;

extern QUEUE	*newQUEUE(void);
extern void	enqueue(QUEUE *items,void *value);
extern void	*dequeue(QUEUE *items);
extern void	*peekQUEUE(QUEUE *items);
extern void	freeQUEUE(QUEUE *items);
extern int	sizeQUEUE(QUEUE *items);

#endif
