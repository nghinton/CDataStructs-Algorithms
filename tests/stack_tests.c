#include "minunit.h"
#include <stack.h>
#include <assert.h>

static STACK *stack = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};

#define NUM_TESTS 3

char *test_newSTACK() 
{
    stack = newSTACK();
    mu_assert(stack != NULL, "Stack failed to initialize");

    return NULL;
}

char *test_push_pop()
{
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++) {
        push(stack, tests[i]);
        mu_assert(peekSTACK(stack) == tests[i], "Wrong next value.");
    }

    mu_assert(sizeSTACK(stack) == NUM_TESTS, "Wrong count on push.");

    for (i = NUM_TESTS - 1; i >= 0; i--) {
        char *val = pop(stack);
        mu_assert(val == tests[i], "Wrong value on pop.");
    }

    mu_assert(sizeSTACK(stack) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_freeSTACK()
{
    freeSTACK(stack);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_newSTACK);
    mu_run_test(test_push_pop);
    mu_run_test(test_freeSTACK);    

    return NULL;
}

RUN_TESTS(all_tests);