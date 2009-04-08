#include "test.h"
#define TRUE 1
#define FALSE 0

int tests_run = 0;
heap *h;

static char * setup() {
    return 0;
}

static char * test_boolean() {
    int a = 0, b = 1, c = -1;
    mu_assert("boolean a", !a);
    mu_assert("boolean not b", b);
    mu_assert("boolean not c", c);
    mu_assert("TRUE", TRUE);
    mu_assert("!FALSE", !FALSE);
    const char* foo = "\n";
    printf("%d\n", strlen(foo));
    return 0;
}

static char * test_atoi() {
    mu_assert("atoi", 3 == atoi("3"));
    mu_assert("atoi 2", 23 == atoi("4"));
}

static char * all_tests() {
    mu_run_test(test_boolean);
    mu_run_test(test_atoi);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
