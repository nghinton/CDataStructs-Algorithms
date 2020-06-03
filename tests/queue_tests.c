#include "minunit.h"
#include <queue.h>
#include <assert.h>

static QUEUE *queue = NULL;
char *tests[] = {"test1 data", "tests2 data", "test3 data"};

char *test_newQUEUE() 
{
    return NULL;
}

char *test_enqueue()
{
    return NULL;
}

char *test_dequeue()
{
    return NULL;
}

char *test_peekQUEUE()
{
    return NULL;
}

char *test_sizeQUEUE()
{
    return NULL;
}

char *test_freeQUEUE()
{
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newQUEUE);
    mu_run_test(test_enqueue);
    mu_run_test(test_dequeue);
    mu_run_test(test_peekQUEUE);
    mu_run_test(test_sizeQUEUE);
    mu_run_test(test_freeQUEUE);    

    return NULL;
}

RUN_TESTS(all_tests);