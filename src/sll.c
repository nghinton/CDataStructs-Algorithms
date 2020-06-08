#include <assert.h>
#include "sll.h"

sll *newSLL() 
{
    sll *p = malloc(sizeof(sll));
    assert(p != NULL);

    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    
    return p;
}

void insertSLL(sll *items,int index,void *value) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    // Allocate a new list node and assign it values
    sllnode *newNode = malloc(sizeof(sll));
    assert(newNode != NULL);
    newNode->value = value;
    newNode->next = NULL;

    // If inserting into a new list
    if (items->head == NULL && items->tail == NULL) {
        items->head = newNode;
        items->tail = newNode;
        items->size++;
        return;
    }
    // If inserting at head
    if (index == 0) {
        newNode->next = items->head;
        items->head = newNode;
    }
    //If inserting at tail
    else if (index == items->size) {
        items->tail->next = newNode;
        items->tail = newNode;
    }
    //insert at index
    else {
        sllnode *curr = items->head;
        sllnode *prev = NULL;
        // Traverse the list to requested index
        for (int i=0; i<index;i++) {
            prev = curr;
            curr = curr->next;
        }
        // Insert node into list
        newNode->next = curr;
        prev->next = newNode;
    }
    // Update the size of the SLL
    items->size++;
}

void *removeSLL(sll *items,int index) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    sllnode *curr, *prev, *temp;
    void *result = NULL;
    curr = items->head;

    // Remove from head
    if (index == 0) {
        // Assign removed value to temp
        temp = items->head;
        // Reassign list head
        items->head = items->head->next;
        // Update the size of the SLL
        items->size--;
        // Return the removed value
        result = temp->value;
        // Free the removed node
        free(temp);
    }
    // Remove from middle and back
    else {
        curr = items->head->next;
        prev = items->head;
        //loop through list
        for (int i=1; i<index; i++) { // i=1 because were not startng at the head
            prev = curr;
            curr = curr->next;
        }
        // Store the value to be removed
        temp = curr;
        // Reassaign prev->next
        prev->next = curr->next;
        // Update the tail if needed
        if(items->tail == curr) {
            items->tail = prev;
        }
        // Update the size of the SLL
        items->size--;
        // Return the removed value
        result = temp->value;
        // Free the removed node
        free(temp);

    }
    return result;
}

void *getSLL(sll *items,int index) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    sllnode *curr, *temp;
    curr = items->head;

    // If it's the head node
    if (index == 0) {
        temp = items->head;
        return temp->value;
    }
    // If the tail node
    else if (index == items->size) {
        temp = items->tail;
        return temp->value;
    } else {
        // Loop through list until the index
        for (int i=0; i<index; i++) {
            curr = curr->next;
        }
        return curr->value;
    }
    return 0;
}

void *setSLL(sll *items, int index, void *value) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    sllnode *curr, *temp;
    curr = items->head;
    void *oldValue;

    //if it's the head node
    if (index == 0) {
        temp = items->head;
        oldValue = temp->value;
        temp->value = value;
        return oldValue;
    }
    //if the last node
    else if (index == items->size) {
        temp = items->tail;
        oldValue = temp->value;
        temp->value = value;
        return oldValue;
    } else {
        // Loop through list until the index
        for (int i=0; i<index; i++) {
            curr = curr->next;
        }
        oldValue = curr->value;
        curr->value = value;
        return oldValue;
    }
    return 0;
}

int sizeSLL(sll *items) 
{
    return items->size;
}

void freeSLL(sll *items) 
{
    if (items->size == 0) {
        free(items);
    } else {
        sllnode *curr, *next;
        curr = items->head;
        for (int i=0; i<items->size; i++) {
            next = curr->next;
            if (curr->value) {
                free(curr->value);
            }
            free(curr);
            curr = next;
        }
    }
}