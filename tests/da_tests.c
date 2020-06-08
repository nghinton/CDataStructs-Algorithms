#include "minunit.h"
#include <da.h>
#include <assert.h>

static DA *da = NULL;

#define NUM_TESTS 100

char *test_newDA() 
{
    da = newDA();
    mu_assert(da != NULL, "Failed to initialize da");
    mu_assert(da->size == 0, "Size initialized incorrectly");
    mu_assert(da->capacity == 1, "Capacity initialized incorrectly");
    
    return NULL;
}

char *test_insertDA_removeDA()
{
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++) {
        int *p = malloc(sizeof(int));
        *p = i;
        insertDAback(da, p);
    }
    mu_assert(sizeDA(da) == NUM_TESTS, "Wrong size after inserting");
    mu_assert(da->capacity == 128, "Wrong capacity after insertion");

    for (i = 0; i < NUM_TESTS; i++) {
        int *t = removeDA(da, 0);
        mu_assert(*t == i, "Wrong value removed");
    }
    mu_assert(sizeDA(da) == 0, "Wrong size after removal");
    mu_assert(da->capacity == 1, "Wrong capacity after removal");

    return NULL;
}

char *test_freeDA()
{
    freeDA(da);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newDA);
    mu_run_test(test_insertDA_removeDA);
    mu_run_test(test_freeDA);    

    return NULL;
}

RUN_TESTS(all_tests);