#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

struct list_el {
   void *value;
   struct list_el *next;
};

typedef struct list_el fifo_node;

typedef struct {
    fifo_node *front;
    fifo_node *back;    
} fifo_queue;

fifo_node *fifo_node_new(void *value);
fifo_queue *fifo_queue_new();
void *dequeue(fifo_queue *fq);
void enqueue(fifo_queue *fq, void *value);
void *peek(fifo_queue *fq);

#endif /* FIFO_QUEUE_H */
