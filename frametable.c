#include "frametable.h"
#include "process.h"

frame_table *frame_table_new(int frame_table_size)
{
    frame_table *f = malloc(sizeof(frame_table));
    f->max = frame_table_size;
    f->count = 0;
    int i;
    for(i = 0; i < f->max; ++i)
    {
        f->framelist[i] = NULL;
    }
    return f;
}

frame_entry *simulate_fifo(frame_table *ft, int page, int cpu_time, int process_id)
{
    frame_entry *entry2 = NULL;
    frame_entry *entry3 = NULL;
    process *process2 = NULL;
    process *process3 = NULL;
    int i;
    
    // if the given page is already in the frame table, go ahead and use it.
    for(i = 0; i < ft->count; ++i) {
        frame_entry *entry = ft->framelist[i];
        if ((!entry->empty && (entry->page == page)) && (entry->process_id == process_id)) {
            entry->PageFault = FALSE;
            return entry;
        }
    }
    
    // otherwise, lets me a new frame entry
    entry2 = frame_entry_new();
    entry2->cpu_time = cpu_time;
    entry2->last_used = 0;
    entry2->page = page;
    entry2->empty = FALSE;
    entry2->process_id = process_id;
    
    // and insert it in a blank slot if there is one
    for (i = ft->count - 1; i >= 0; i--) {
        entry3 = ft->framelist[i];
        if (entry3->empty) {
            entry2->frame_id = i;
            ft->framelist[entry2->frame_id] = entry2;
            process *process1 = ProcessArray[process_id];
            process1->PageFaults++;
            entry2->PageFault = TRUE;
            return entry2;
        }
    }
    
    // otherwise we're going to pick a victim frame to evict
    entry3 = ft->framelist[ft->count - 1];
    int num2 = entry3->cpu_time;
    int num3 = entry3->frame_id;
    int j;
    for (j = ft->count - 2; j >= 0; j--) {
        entry3 = ft->framelist[j];
        if (entry3->cpu_time < num2) {
            num2 = entry3->cpu_time;
            num3 = entry3->frame_id;
        }
    }
    entry2->frame_id = num3;
    entry3 = ft->framelist[num3];
    process3 = ProcessArray[entry3->process_id];
    process3->TotalResidency += cpu_time - entry3->cpu_time;
    process3->Evicted++;
    ft->framelist[num3] = entry2;
    process2 = ProcessArray[process_id];
    process2->PageFaults++;
    entry2->PageFault = TRUE;
    return entry2;
}