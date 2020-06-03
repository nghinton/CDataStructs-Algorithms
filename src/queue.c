#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cda.h"
#include "queue.h"

struct QUEUE{
	CDA *CDA;
};

QUEUE *newQUEUE()
{
	QUEUE *p = malloc(sizeof(QUEUE));
	assert(p != 0);

	p->CDA = newCDA();
	assert(p->CDA != 0);

	return p;
}

void enqueue(QUEUE *items,void *value)
{
	insertCDAback(items->CDA, value);
}

void *dequeue(QUEUE *items)
{
	assert(sizeCDA(items->CDA) != 0);
	void *dequeued = removeCDAfront(items->CDA);
	return dequeued;
}

void *peekQUEUE(QUEUE *items)
{
	assert(sizeCDA(items->CDA) != 0);
	void *peeked = getCDA(items->CDA, 0);
	return peeked;
}

void freeQUEUE(QUEUE *items)
{
	freeCDA((CDA *)items->CDA);
	free((QUEUE *)items);
}

int sizeQUEUE(QUEUE *items)
{
	int size = sizeCDA(items->CDA);
	return size;
}

