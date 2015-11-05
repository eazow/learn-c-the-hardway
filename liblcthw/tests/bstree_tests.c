#include "minunit.h"
#include <lcthw/bstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>
#include <time.h>

BSTree *tree = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(BSTreeNode *node)
{
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(BSTreeNode *node)
{
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;

    if(traverse_called == 2) {
        return 1;
    }
    else {
        return 0;
    }
}

char *test_create()
{
    tree = bstree_create(NULL);
    mu_assert(tree != NULL, "Failed to create tree.");

    return NULL;
}

char *test_destroy()
{
    bstree_destroy(tree);

    return NULL;
}

char *test_get_and_set()
{
    int rc = bstree_set(tree, &test1, &expect1);
    mu_assert(rc == 0, "Falied to set &test1");
    bstring result = bstree_get(tree, &test1);
    mu_assert(result == &expect1, "Wrong value for test1.");

    return NULL;
}

char *test_traverse()
{
    return NULL;
}

char *test_delete()
{
    bstring deleted = (bstring)bstree_delete(tree, &test1);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect1, "Should get test1");
    bstring result = bstree_get(tree, &test1);
    mu_assert(result == NULL, "Should delete.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_and_set);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
