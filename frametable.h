#include <stdlib.h>
#include "frameentry.h"
#include "process.h"
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 100000

#ifndef FRAME_TABLE_H
#define FRAME_TABLE_H

process *ProcessArray[4];

typedef struct {
    int count;
    int max;
    frame_entry *framelist[MAX_SIZE];
} frame_table;

frame_table *frame_table_new(int frame_table_size);
frame_entry *simulate_fifo(frame_table *ft, int page, int cpu_time, int process_id);

#endif /* FRAME_TABLE_H */