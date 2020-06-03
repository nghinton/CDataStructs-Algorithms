#include "minunit.h"
#include <da.h>
#include <assert.h>

static DA *da = NULL;
char *tests[] = {"test1 data", "tests2 data", "test3 data"};

char *test_newDA() 
{
    return NULL;
}

char *test_insertDA()
{
    return NULL;
}

char *test_removeDA()
{
    return NULL;
}

char *test_getDA()
{
    return NULL;
}

char *test_setDA()
{
    return NULL;
}

char *test_sizeDA()
{
    return NULL;
}

char *test_freeDA()
{
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newDA);
    mu_run_test(test_insertDA);
    mu_run_test(test_removeDA);
    mu_run_test(test_getDA);
    mu_run_test(test_setDA);
    mu_run_test(test_sizeDA);
    mu_run_test(test_freeDA);    

    return NULL;
}

RUN_TESTS(all_tests);