#ifndef algorithms_h
#define algorithms_h

#include "da.h"

typedef int (*DA_compare) (const void *a, const void *b);

int DA_qsort(DA *items, DA_compare cmp);
int DA_heapsort(DA *items, DA_compare cmp);
int DA_mergesort(DA *items, DA_compare cmp);
int DA_insertionsort(DA *items, DA_compare cmp);
int DA_radixsort(DA *items, DA_compare cmp);
int DA_binarysearch(DA *items, DA_compare cmp);

#endif