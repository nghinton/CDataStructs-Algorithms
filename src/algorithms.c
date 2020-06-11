#include "algorithms.h"
#include "da.h"
#include <stdlib.h>

// A utility function to swap two elements 
void swap(void* a, void* b) 
{ 
    void *temp;
    temp = *(void**)a;
    *(void**)a = *(void**)b;
    *(void**)b = temp;
} 

int partition(void **array, int low, int high, DA_compare cmp) 
{
    // Choose the highest index as the pivot
    // at least mostly consistent
    void *pivot = array[high];

    // Index of smaller element
    int i = low-1;

    for (int j=low; j <= high-1; j++) {
        // If current element is smaller than the pivot
        int rc = cmp(array[j], pivot);
        if (rc < 0) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[high]);
    return (i + 1);
}

void quickSort(void **array, int low, int high, DA_compare cmp) 
{
    if (low < high) {

        // Get the partitioned index
        int pi = partition(array, low, high, cmp);

        // Recursively sort the array around the partitioned index
        quickSort(array, low, pi -1, cmp);
        quickSort(array, pi + 1, high, cmp);
    }
}

int DA_qsort(DA *items, DA_compare cmp)
{
    quickSort(items->array, 0, sizeDA(items)-1, cmp);
    return 0;
}

void merge(void **array, int low, int middle, int high, DA_compare cmp) 
{ 
    int i, j, k; 
    int n1 = middle - low + 1; 
    int n2 = high - middle; 
  
    // create temp arrays 
    void **Left = malloc(sizeof(void *) * n1); 
    void **Right = malloc(sizeof(void *) * n2); 
  
    // Copy data to temp arrays L[] and R[] 
    for (i = 0; i < n1; i++) 
        Left[i] = array[low + i]; 
    for (j = 0; j < n2; j++) 
        Right[j] = array[middle + 1 + j]; 
  
    // Merge the temp arrays back into arr[left..right]
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = low; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        if (cmp(Left[i], Right[j]) <= 0) { 
            array[k] = Left[i]; 
            i++; 
        } 
        else { 
            array[k] = Right[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) { 
        array[k] = Left[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
        array[k] = Right[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(void **array, int low, int high, DA_compare cmp) 
{
if (low < high) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int middle = (low + high) / 2; 
  
        // Sort first and second halves 
        mergeSort(array, low, middle, cmp); 
        mergeSort(array, middle + 1, high, cmp); 
  
        merge(array, low, middle, high, cmp); 
    } 
}

int DA_mergesort(DA *items, DA_compare cmp)
{
    mergeSort(items->array, 0, sizeDA(items)-1, cmp);
    return 0;
}

void heapify(void **array, int size, int index, DA_compare cmp) 
{ 
    int largest = index; // Initialize largest as root 
    int left = 2*index + 1; // left = 2*i + 1 
    int right = 2*index + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if ((left < size) && (cmp(array[left], array[largest]) > 0)) 
        largest = left; 
  
    // If right child is larger than largest so far 
    if ((right < size) && (cmp(array[right], array[largest]) > 0)) 
        largest = right; 
  
    // If largest is not root 
    if (largest != index) 
    { 
        swap(&array[index], &array[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(array, size, largest, cmp); 
    } 
} 

void heapSort(void **array, int size, DA_compare cmp) 
{ 
    int index = size / 2 - 1;

    // Build max heap with given array
    for (int i=index; i>=0; i--) {
        heapify(array, size, i, cmp);
    }

    // Sort the array
    for (int i=size-1; i>0; i--) { 
        // Move current max root to end 
        swap(&array[0], &array[i]); 
  
        // Call max heapify on the reduced heap 
        heapify(array, i, 0, cmp); 
    } 
} 

int DA_heapsort(DA *items, DA_compare cmp)
{
    heapSort(items->array, sizeDA(items), cmp);
    return 0;
}

int DA_insertionsort(DA *items, DA_compare cmp)
{
    void **array = items->array;
    int size = sizeDA(items);

    int j;
    void *key; 
    for (int i=1; i < size; i++) { 
        key = array[i]; 
        j = i - 1; 
  
        // Move values greater than key down the array
        while (j >= 0 && cmp(array[j], key) > 0) { 
            array[j + 1] = array[j]; 
            j = j - 1; 
        } 
        array[j + 1] = key; 
    }

    return 0;
}

// A utility function to get maximum value in arr[] 
int getMax(void **array, int size) 
{ 
    int max = *(int *)array[0]; 
    for (int i = 1; i < size; i++) {
        if ( *(int *) array[i] > max ) { 
            max = *(int *) array[i]; 
        }
    }
    return max; 
} 

void countSort(void **array, int size, int exp) 
{ 
    // Create output array
    void **output = malloc(sizeof(void *) * size); 

    int count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (int i=0; i < size; i++) 
        count[ ((*(int *)array[i])/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (int i=1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (int i=size-1; i >= 0; i--) 
    { 
        output[count[ ((*(int *)array[i])/exp)%10 ] - 1] = array[i]; 
        count[ ((*(int *)array[i])/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (int i=0; i < size; i++) 
        array[i] = output[i]; 

    // Free ouput array
    free(output);
} 

int DA_radixsort(DA *items, DA_compare cmp)
{
    void **array = items->array;
    int size = sizeDA(items);

    // Find the maximum number to know number of digits 
    int max = 9; //getMax(array, size); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; max/exp > 0; exp *= 10) { 
        countSort(array, size, exp); 
    }

    return 0;
}