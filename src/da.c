#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"

DA *
newDA(void)
	{
	DA *p = malloc(sizeof(DA));
	assert(p != 0);

	p->array = malloc(sizeof(void *));
	assert(p->array != 0); 

	p->size = 0;
	p->capacity = 1;

	return p;
	}

void insertDA(DA *items,int index,void *value)
{
	// If full, then double the array
	if (items->size == items->capacity) {
		items->array = realloc(items->array, sizeof(void *)*(items->capacity*2));
		assert(items->array != 0);
		items->capacity = items->capacity*2;
	}
	// Insert at back
	if (index == items->size) { 
		items->array[items->size] = value;
	}
	// Insert at front or middle
	else {
		for (int i=items->size; i>index; --i) {
			items->array[i] = items->array[i-1];
		}
		items->array[index] = value;
	}
	// Increment size
	items->size++;

}

void *removeDA(DA *items,int index)
{
	assert(items->size>0);
	assert(index >= 0 && index < items->size);
	// Store value to be removed
	void *removed = items->array[index];
	// Update size
	items->size--;

	// Shift every value above the index 1 lower
	for (int i=index; i<items->size; ++i) {
		items->array[i]=items->array[i+1];
	}

	// Check capacity to size ratio and update accordingly
	if (items->size == 0) {items->capacity = 1; return removed;}
	if (items->size*4 <= items->capacity) {
		// reallocate the array to its new size
		items->array = realloc(items->array, sizeof(void *)*(items->capacity));
		assert(items->array != 0);
		// update capacity
		items->capacity = items->capacity/2;
	}

	// Return removed value
	return removed;
}

void *
getDA(DA *items,int index)
	{
	assert(index>=0);
	assert(index<items->size);
	return items->array[index];
	}

void *
setDA(DA *items, int index, void *value)
	{
	assert(index>=0);
	assert(index<=items->size);
	void *temp;
	// If the index is equal to size, insert the value
	if (index == items->size) {
		insertDA(items,index,value);
		return temp = NULL;
	}
	// Otherwise, store the value to be written over and insert the given value
	else {
		temp = items->array[index];
		items->array[index] = value;
		return temp;
	}
	}

int
sizeDA(DA *items)
	{
	return items->size;
	}

void freeDA(DA *items)
{
	if (items->size != 0) {
		for (int i=0; i<items->size; i++) {
			free(items->array[i]);
		}
	}
	free(items->array);
	free((DA *) items);
	return;
}