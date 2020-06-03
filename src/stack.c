#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "da.h"

struct STACK{
	DA *DA;
};

STACK *newSTACK(void)
{
	STACK *p = malloc(sizeof(STACK));
	assert(p != 0);

	p->DA = newDA();
	assert(p->DA != 0);

	return p;
}

void push(STACK *items,void *value)
{
	insertDAback(items->DA, value);
}

void *pop(STACK *items)
{
	assert(sizeDA(items->DA) != 0);
	void *popped = removeDA(items->DA, sizeDA(items->DA)-1);
	return popped;
}

void *peekSTACK(STACK *items)
{
	assert(sizeDA(items->DA) != 0);
	void *peeked = getDA(items->DA, sizeDA(items->DA)-1);
	return peeked;
}

void freeSTACK(STACK *items)
{
	freeDA((DA *)items->DA);
	free((STACK *)items);
}

int sizeSTACK(STACK *items)
{
	int size = sizeDA(items->DA);
	return size;
}
