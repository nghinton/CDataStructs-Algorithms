#include <assert.h>
#include "dll.h"

dll *newDLL() 
{    
    dll *p = malloc(sizeof(dll));
    assert(p != NULL);

    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    
    return p;
}

void insertDLL(dll *items,int index,void *value) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    // Allocate a new list node and assign it values
    dllnode *newNode = malloc(sizeof(dll));
    assert(newNode != NULL);
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

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
        items->head->prev = newNode;
        items->head = newNode;
    }
    //If inserting at tail
    else if (index == items->size) {
        items->tail->next = newNode;
        newNode->prev = items->tail;
        items->tail = newNode;
    }
    //insert at index
    else {
        dllnode *curr = items->head;
        dllnode *prev = NULL;
        // Traverse the list to requested index
        for (int i=0; i<index;i++) {
            prev = curr;
            curr = curr->next;
        }
        // Insert node into list
        newNode->next = curr;
        curr->prev = newNode;
        prev->next = newNode;
        newNode->prev = prev;
    }
    // Update the size of the SLL
    items->size++;
}

void *removeDLL(dll *items, int index) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    dllnode *curr, *prev, *temp;
    void *result = NULL;
    curr = items->head;

    // Remove from head
    if (index == 0) {
        // Assign removed value to temp
        temp = items->head;
        // Reassign list head
        items->head = items->head->next;
        items->head->prev = NULL;
        // Update the size of the SLL
        items->size--;
        // Return the removed value
        result = temp->value;
        // Free the removed node
        free(temp);
    }
    // Remove from the back
    else if (index == items->size-1) {
        // Assign removed value to temp
        temp = items->tail;
        // Reassign list prev
        items->tail = items->tail->prev;
        items->tail->next = NULL;
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
        prev->next->prev = prev;
        // Update the size of the SLL
        items->size--;
        // Return the removed value
        result = temp->value;
        // Free the removed node
        free(temp);

    }
    return result;
}

void *getDLL(dll *items, int index) 
{
    // Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    dllnode *curr, *temp;
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
        // Loop throught the list until the index
        for (int i=0; i<index; i++) {
            curr = curr->next;
        }
        return curr->value;
    }

    return 0;
}

void *setDLL(dll *items, int index, void *value) 
{
// Make sure the index is within bounds
    assert(index >= 0 && index < items->size);

    dllnode *curr, *temp;
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

int sizeDLL(dll *items) 
{
    return items->size;
}

void freeDLL(dll *items) 
{
if (items->size == 0) {
        free(items);
    } else {
        dllnode *curr, *next;
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