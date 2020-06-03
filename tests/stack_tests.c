#include "minunit.h"
#include <stack.h>
#include <assert.h>

static STACK *stack = NULL;
char *tests[] = {"test1 data", "tests2 data", "test3 data"};

char *test_newSTACK() 
{
    return NULL;
}

char *test_push()
{
    return NULL;
}

char *test_pop()
{
    return NULL;
}

char *test_peekSTACK()
{
    return NULL;
}

char *test_sizeSTACK()
{
    return NULL;
}

char *test_freeSTACK()
{
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newSTACK);
    mu_run_test(test_push);
    mu_run_test(test_pop);
    mu_run_test(test_peekSTACK);
    mu_run_test(test_sizeSTACK);
    mu_run_test(test_freeSTACK);    

    return NULL;
}

RUN_TESTS(all_tests);