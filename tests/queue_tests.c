#include "minunit.h"
#include <queue.h>
#include <assert.h>

static QUEUE *queue = NULL;
char *tests[] = {"test1 data", "tests2 data", "test3 data"};

#define NUM_TESTS 3

char *test_newQUEUE() 
{
    queue = newQUEUE();
    mu_assert(queue != NULL, "Queue failed to initialize");

    return NULL;
}

char *test_enqueue_dequeue()
{
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++) {
        enqueue(queue, tests[i]);
        mu_assert(peekQUEUE(queue) == tests[0], "Wrong next value.");
    }

    mu_assert(sizeQUEUE(queue) == NUM_TESTS, "Wrong count on enqueue.");

    for (i = 0; i < NUM_TESTS; i++) {
        char *val = dequeue(queue);
        mu_assert(val == tests[i], "Wrong value on dequeue.");
    }

    mu_assert(sizeQUEUE(queue) == 0, "Wrong count after dequeue.");

    return NULL;
}

char *test_freeQUEUE()
{
    freeQUEUE(queue);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newQUEUE);
    mu_run_test(test_enqueue_dequeue);
    mu_run_test(test_freeQUEUE);    

    return NULL;
}

RUN_TESTS(all_tests);