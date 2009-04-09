#include "frameentry.h"

frame_entry *frame_entry_new()
{
    frame_entry *f = malloc(sizeof(frame_entry));
    f->cpu_time  = 0;
    f->empty     = FALSE;
    f->frame_id  = 0;
    f->last_used = 0;
    f->page      = 0;
    f->PageFault = FALSE;
    f->process_id= 0;
    return f;
}
