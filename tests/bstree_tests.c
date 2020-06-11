#include "minunit.h"
#include <bstree.h>
#include <assert.h>
#include <bstrlib.h>
#include <stdlib.h>
#include <time.h>

BST *tree = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("xest data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(BSTnode * node)
{
    debug("KEY: %s", bdata((bstring) node->key));
    (void) node;
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(BSTnode *node)
{
    debug("KEY: %s", bdata((bstring) node->key));
    (void) node;
    traverse_called++;

    if (traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

char *test_create()
{
    tree = createBST(NULL);
    mu_assert(tree != NULL, "Failed to create tree.");

    return NULL;
}

char *test_destroy()
{
    destroyBST(tree);

    return NULL;
}

char *test_get_set()
{
    int rc = setBST(tree, &test1, &expect1);
    mu_assert(rc == 0, "Failed to set &test1");
    bstring result = getBST(tree, &test1);
    mu_assert(result == &expect1, "Wrong value for test1.");

    rc = setBST(tree, &test2, &expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = getBST(tree, &test2);
    mu_assert(result == &expect2, "Wrong value for test2.");

    rc = setBST(tree, &test3, &expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = getBST(tree, &test3);
    mu_assert(result == &expect3, "Wrong value for test3.");

    return NULL;
}

char *test_traverse()
{
    int rc = traverseBST(tree, traverse_good_cb);
    mu_assert(rc == 0, "Failed to traverse.");
    mu_assert(traverse_called == 3, "Wrong count traverse.");

    traverse_called = 0;
    rc = traverseBST(tree, traverse_fail_cb);
    mu_assert(rc == 1, "Failed to traverse.");
    mu_assert(traverse_called == 2, "Wrong count traverse for fail.");

    return NULL;
}

char *test_remove()
{
    bstring deleted = (bstring) removeBST(tree, &test1);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect1, "Should get test1");
    bstring result = getBST(tree, &test1);
    mu_assert(result == NULL, "Should delete.");

    deleted = (bstring) removeBST(tree, &test1);
    mu_assert(deleted == NULL, "Should get NULL on delete");

    deleted = (bstring) removeBST(tree, &test2);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect2, "Should get test2");
    result = getBST(tree, &test2);
    mu_assert(result == NULL, "Should delete.");

    deleted = (bstring) removeBST(tree, &test3);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect3, "Should get test3");
    result = getBST(tree, &test3);
    mu_assert(result == NULL, "Should delete.");

    // test deleting non-existent stuff
    deleted = (bstring) removeBST(tree, &test3);
    mu_assert(deleted == NULL, "Should get NULL");

    return NULL;
}

char *test_fuzzing()
{
    BST *store = createBST(NULL);
    int i = 0;
    int j = 0;
    bstring numbers[100] = { NULL };
    bstring data[100] = { NULL };
    srand((unsigned int)time(NULL));

    for (i = 0; i < 100; i++) {
        int num = rand();
        numbers[i] = bformat("%d", num);
        data[i] = bformat("data %d", num);
        setBST(store, numbers[i], data[i]);
    }

    for (i = 0; i < 100; i++) {
        bstring value = removeBST(store, numbers[i]);
        mu_assert(value == data[i],
                "Failed to delete the right number.");

        mu_assert(removeBST(store, numbers[i]) == NULL,
                "Should get nothing.");

        for (j = i + 1; j < 99 - i; j++) {
            bstring value = getBST(store, numbers[j]);
            mu_assert(value == data[j],
                    "Failed to get the right number.");
        }

        bdestroy(value);
        bdestroy(numbers[i]);
    }

    destroyBST(store);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_remove);
    mu_run_test(test_destroy);
    mu_run_test(test_fuzzing);

    return NULL;
}

RUN_TESTS(all_tests);