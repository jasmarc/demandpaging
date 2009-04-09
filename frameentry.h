#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#ifndef FRAME_ENTRY_H
#define FRAME_ENTRY_H

typedef struct {
    int cpu_time;
    int empty;
    int frame_id;
    int last_used;
    int page;
    int PageFault;
    int process_id;
} frame_entry;

frame_entry *frame_entry_new();

#endif /* FRAME_ENTRY_H */
