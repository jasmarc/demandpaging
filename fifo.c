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

fifo_node *dequeue(fifo_queue *fq)
{
    fifo_node *fn = fq->front;
    fq->front = fq->front->next;
    return fn;
}

void queue(fifo_queue *fq, void *value)
{
    fifo_node *fn = fifo_node_new(value);
    fq->back->next = fn;
    fq->back = fn;
}
