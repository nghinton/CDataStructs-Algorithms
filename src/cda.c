#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cda.h"

CDA *newCDA(void)
{
	CDA *p = malloc(sizeof(CDA));
	assert(p != 0);

	p->array = malloc(sizeof(void *));
	assert(p->array != 0);

	p->front = 0;
	p->back = 0;
	p->size = 0;
	p->capacity = 1;

	return p;
}

void insertCDA(CDA *items,int index,void *value)
{
	// If full then double the array
	if (items->size == items->capacity) {
		// Create a new array of the approporaite size
		void **newArray = malloc(sizeof(void *)*items->capacity*2);
		assert(newArray != 0);
		// Copy over values into the new array
		for (int i=0; i<items->size; ++i) {
			newArray[i] = getCDA(items, i);
		}
		// Free the old array
		free(items->array);
		// Assign to the new array
		items->array = newArray;
		assert(items->array != 0);
		// Reset cda values
		items->capacity = items->capacity*2;
		items->front = 0;
		items->back = items->size-1;
	}
	// Inserting at the front
	if (index == 0) {
		if (items->front == 0) {
			items->front = items->capacity-1;
		} else {
			items->front--;
		}
		items->array[items->front] = value;
	}
	// Inserting at the back
	else if (index == items->size) {
		items->back++;
		items->array[items->back] = value;
	}
	// Inserting in the middle
	else {
		// Insert in front half
		if (index < items->size/2) {
			if (items->front == 0) {
				items->front = items->capacity-1;
			} else {
				items->front--;
			}
			for (int i=0; i<=index; i++) {
				items->array[(items->front+i)%items->capacity] = 
					items->array[(items->front+i+1)%items->capacity];
			}
			items->array[(items->front+index)%items->capacity] = value;
		}
		// Insert in back half
		else {
			for(int i=items->size; i>=index; --i) {
				items->array[(items->front+i)%items->capacity] = 
					items->array[(items->front+i-1)%items->capacity]; 
			}
			items->array[(items->front+index)%items->capacity] = value;
			items->back++;
		}
	}
	//Increment size
	items->size++;
}

void *removeCDA(CDA *items,int index)
{
	assert(items->size>0);
	assert(index >= 0 && index < items->size);
	// Store value to be removed
	void *removed = getCDA(items, index);
	// Update size
	items->size--;
	// Remove from front
	if (index == 0) {
		// Update front
		items->front++;
		if (items->front == items->capacity) {items->front = 0;}
	}
	// Remove from back
	else if (index == items->size-1) {
		// Update back
		if  (items->back > 0) {items->back--;}
	}
	// Remove from middle
	else {
		//Remove from front  half
		if (index < items->size/2) {
			for (int i=index; i>0; i--) {
				items->array[(items->front+i)%items->capacity] = 
					items->array[(items->front+i-1)%items->capacity];
			}
			items->front++;
			if (items->front == items->capacity) {items->front = 0;}
		}
		// Remove from back half
		else {
			for (int i=index; i<items->size; i++) {
				items->array[(items->front+i)%items->capacity] = 
					items->array[(items->front+i+1)%items->capacity];
			}
			if (items->back > 0) {items->back--;}
		}
	}

	// Check capacity to size ratio and update accordingly
	if (items->size == 0) {items->capacity = 1; return removed;}
	if (items->size*4 <= items->capacity) {
		// Create a new array of the approporaite size
		void **newArray = malloc(sizeof(void *)*items->capacity/2);
		assert(newArray != 0);
		// Copy over values into the new array
		for (int i=0; i<items->size; ++i) {
			newArray[i] = getCDA(items, i);
		}
		// Free the old array
		free(items->array);
		// Assign to the new array
		items->array = newArray;
		assert(items->array != 0);
		// Reset cda values
		items->capacity = items->capacity/2;
		items->front = 0;
		items->back = items->size-1;
	}

	// Return removed value
	return removed;
}

void *getCDA(CDA *items,int index)
{
	assert(index>=0);
	assert(index<items->size);
	return items->array[(items->front+index)%items->capacity];
}

void *setCDA(CDA *items, int index, void *value)
{
	assert(index>=-1);
	assert(index<=items->size);
	void *temp;
	// If the index is equal to size, insert at back
	if (index == items->size) {
		insertCDAback(items,value);
		return temp = NULL;
	}
	// If the index is -1, insert at front
	else if (index == -1) {
		insertCDAfront(items,value);
		return temp = NULL;
	}
	// Otherwise, store the value to be written over and insert the value
	else {
		temp = items->array[(items->front+index)%items->capacity];
		items->array[(items->front+index)%items->capacity] = value;
		return temp;
	}
}

int sizeCDA(CDA *items)
{
	return items->size;
}

void freeCDA(CDA *items)
{
	if (items->size != 0) {
		for (int i=0; i<items->size; i++) {
			free(items->array[i]);
		}
	}
	free(items->array);
	free((CDA *) items);
	return;
}