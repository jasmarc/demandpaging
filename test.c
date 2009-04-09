#include "test.h"
#include "process.h"
#include "frameentry.h"
#include "frametable.h"
#include "a4.h"
#include "fifo.h"
#include "assert.h"

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

static char * test_process() {
    process *p = NULL;
    p = process_new(1,1,1,1,1);
    mu_assert("p-> == 1", p->A == 1);
    return 0;
}

static char * test_frame_entry() {
    frame_entry *fe = frame_entry_new();
    mu_assert("fe->PageFault == FALSE", fe->PageFault == FALSE);
    return 0;
}

static char * test_frame_table() {
    frame_table *ft = frame_table_new(2);
    ft->framelist[0] = frame_entry_new();
    mu_assert("frame table not null", ft != NULL);
    mu_assert("ft->framelist", ft->framelist[0] != NULL);
    mu_assert("ft->max", ft->max == 2);
    mu_assert("ft->count", ft->count == 2);
    return 0;
}

static char * test_fifo() {
    fifo_queue *fq = fifo_queue_new();
    mu_assert("front should be null", fq->front == NULL);
    mu_assert("back should be null", fq->back == NULL);
    mu_assert("dequeue an empty queue", dequeue(fq) == NULL);
    int *a, *b;
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    *a = 5;
    *b = 6;
    enqueue(fq, a);
    enqueue(fq, b);
    int *c;
    c = peek(fq);
    printf("c = %d", *c);
    mu_assert("test peek", *c == 5);
    int *x, *y;
    x = dequeue(fq);
    y = dequeue(fq);
    printf("a = %d, b = %d\n", *a, *b);
    printf("x = %d, y = %d\n", *x, *y);
    mu_assert("*x == 6", *x == 5);
    mu_assert("*y == 5", *y == 6);
    return 0;
}

static char * test_assert() {
    assert(1 == 1);
    return 0;
}

static char * all_tests() {
    mu_run_test(setup);
    mu_run_test(test_boolean);
    mu_run_test(test_atoi);
    mu_run_test(test_array_of_pointers);
    mu_run_test(test_process);
    mu_run_test(test_frame_entry);
    mu_run_test(test_frame_table);
    mu_run_test(test_fifo);
    mu_run_test(test_assert);
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
