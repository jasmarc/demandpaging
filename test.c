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
    mu_assert("atoi 2", 23 != atoi("4"));
    printf("hello\n");
    return 0;
}

static char * test_array_of_pointers() {
    int *array_of_pointers[3];
    array_of_pointers[0] = malloc(sizeof(int));
    array_of_pointers[1] = malloc(sizeof(int));
    array_of_pointers[2] = malloc(sizeof(int));
    int j, i = 5;
    array_of_pointers[0] = &i;
    for(j = 0; j < 3; j++)
        printf("the variable at address %p has value %d\n", 
            array_of_pointers[j], *array_of_pointers[j]);
    
    thing *array_of_pointers2[3];
    array_of_pointers2[0] = malloc(sizeof(thing));
    array_of_pointers2[1] = malloc(sizeof(thing));
    array_of_pointers2[2] = malloc(sizeof(thing));
    thing *foo = malloc(sizeof(thing));
    foo->arrive = 12;
    array_of_pointers2[0] = foo;
    array_of_pointers2[1]->arrive = 23;
    for(j = 0; j < 3; j++)
        printf("the variable at address %p has value %d\n", 
            array_of_pointers2[j], array_of_pointers2[j]->arrive);
    return 0;
}

static char * all_tests() {
    mu_run_test(setup);
    mu_run_test(test_boolean);
    mu_run_test(test_atoi);
    mu_run_test(test_array_of_pointers);
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
