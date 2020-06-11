#include "minunit.h"
#include <algorithms.h>
#include <string.h>

int test_cmp_int(int *a, int *b) 
{
    if (*a < *b) return -1;
    if (*a == *b) return 0;
    else return 1;
}

DA *create_numbers() 
{
    DA *results = newDA();

    for(int i=0; i<5; i++) {
        int *val = malloc(sizeof(int));
        *val = rand() % 10;
        insertDAback(results, val);
    }

    return results;
}

int is_sorted_int(DA *array) 
{
    for (int i=0; i<sizeDA(array) - 1; i++) {
        int *a = getDA(array, i);
        int *b = getDA(array, i+1);
        if ( *a > *b) {
            return 0;
        }
    }
    return 1;
}

char *run_sort_test(int (*func) (DA *, DA_compare),
        const char *name)
{
    (void) name;

    DA *words = create_numbers();
    mu_assert(!is_sorted_int(words), "Words should start not sorted.");

    debug("--- Testing %s sorting algorithm", name);
    int rc = func(words, (DA_compare) test_cmp_int);
    mu_assert(rc == 0, "sort failed");
    mu_assert(is_sorted_int(words), "didn't sort it");

    freeDA(words);

    return NULL;
}

char *test_qsort()
{
    return run_sort_test(DA_qsort, "qsort");
}

char *test_mergesort()
{
    return run_sort_test(DA_mergesort, "mergesort");
}

char *test_heapsort()
{
    return run_sort_test(DA_heapsort, "heapsort");
}

char *test_insertionsort()
{
    return run_sort_test(DA_insertionsort, "insertionsort");
}

char *test_radixsort() 
{
    return run_sort_test(DA_radixsort, "radixsort");
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_qsort);
    mu_run_test(test_mergesort);
    mu_run_test(test_heapsort);
    mu_run_test(test_insertionsort); 
    mu_run_test(test_radixsort);

    return NULL;
}

RUN_TESTS(all_tests);