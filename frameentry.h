#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct {
    int cpu_time;
    int empty;
    int frame_id;
    int last_used;
    int page;
    int PageFault;
    int process_id;
} frame_entry;

void frame_entry_new(frame_entry *f);
