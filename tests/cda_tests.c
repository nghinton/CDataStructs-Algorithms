#include "minunit.h"
#include <cda.h>
#include <assert.h>

static CDA *cda = NULL;

#define NUM_TESTS 100

char *test_newCDA() 
{
    cda = newCDA();
    mu_assert(cda != 0, "Failed to initialize cda");
    mu_assert(cda->front == 0, "Front initialized incorrectly");
    mu_assert(cda->back == 0, "Back initialized incorrectly");
    mu_assert(cda->size == 0, "Size initialized incorrectly");
    mu_assert(cda->capacity == 1, "Capacity initialized incorrectly");

    return NULL;
}

char *test_insertCDA_removeCDA()
{
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++) {
        int *p = malloc(sizeof(int));
        *p = i;
        insertCDAback(cda, p);
    }
    mu_assert(sizeCDA(cda) == NUM_TESTS, "Wrong size after inserting");
    mu_assert(cda->capacity == 128, "Wrong capacity after insertion");

    for (i = 0; i < NUM_TESTS; i++) {
        int *t = removeCDA(cda, 0);
        mu_assert(*t == i, "Wrong value removed");
    }
    mu_assert(sizeCDA(cda) == 0, "Wrong size after removal");
    mu_assert(cda->capacity == 1, "Wrongn capacity after removal");

    return NULL;
}

char *test_freeCDA()
{
    freeCDA(cda);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newCDA);
    mu_run_test(test_insertCDA_removeCDA);
    mu_run_test(test_freeCDA);    

    return NULL;
}

RUN_TESTS(all_tests);