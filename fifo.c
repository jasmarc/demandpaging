#include <stdlib.h>
#include "fifo.h"

fifo_node *fifo_node_new(void *value)
{
    fifo_node *fn = malloc(sizeof(fifo_node));
    fn->next = NULL;
    fn->value = value;
    return fn;
}

fifo_queue *fifo_queue_new()
{
    fifo_queue *fq = malloc(sizeof(fifo_queue));
    fq->front = NULL;
    fq->back = NULL;
    return fq;
}

void *dequeue(fifo_queue *fq)
{
    fifo_node *fn = fq->front;
    
    if(fq->front != NULL && fq->front->next == NULL) {
        fq->front = fq->back = NULL;
    }
    else if (fq->front != NULL) {
        fq->front = fq->front->next;
    }
    return fn == NULL ? NULL : fn->value;
}

void enqueue(fifo_queue *fq, void *value)
{
    fifo_node *fn = fifo_node_new(value);
    if(fq->back == NULL) {
        fq->back = fn;
        fq->front = fq->back;
    }
    else {
        fq->back->next = fn;
        fq->back = fn;
    }
}

void *peek(fifo_queue *fq)
{
    fifo_node *fn = fq->front;
    return fn == NULL ? NULL : fn->value;
}
