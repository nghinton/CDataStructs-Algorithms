#include "minunit.h"
#include <cda.h>
#include <assert.h>

static CDA *cda = NULL;
char *tests[] = {"test1 data", "tests2 data", "test3 data"};

char *test_newCDA() 
{
    return NULL;
}

char *test_insertCDA()
{
    return NULL;
}

char *test_removeCDA()
{
    return NULL;
}

char *test_getCDA()
{
    return NULL;
}

char *test_setCDA()
{
    return NULL;
}

char *test_sizeCDA()
{
    return NULL;
}

char *test_freeCDA()
{
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newCDA);
    mu_run_test(test_insertCDA);
    mu_run_test(test_removeCDA);
    mu_run_test(test_getCDA);
    mu_run_test(test_setCDA);
    mu_run_test(test_sizeCDA);
    mu_run_test(test_freeCDA);    

    return NULL;
}

RUN_TESTS(all_tests);