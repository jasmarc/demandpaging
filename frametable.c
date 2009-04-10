#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include "frametable.h"
#include "process.h"
#include "assert.h"

frame_table *frame_table_new(int frame_table_size)
{
    frame_table *f = malloc(sizeof(frame_table));
    f->max = frame_table_size;
    f->count = frame_table_size;
    assert(f->count > 0);
    int i;
    for(i = 0; i < f->max; ++i) {
        f->framelist[i] = NULL;
    }
    for(i = 0; i < frame_table_size; ++i) {
    frame_entry *fe = frame_entry_new();
    fe->empty = TRUE;
    f->framelist[i] = fe;
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
    for(i = ft->count - 1; i >= 0; i--) {
        frame_entry *entry = ft->framelist[i];
        assert(entry != NULL);
        if ((!entry->empty && (entry->page == page)) && (entry->process_id == process_id)) {
            printf("Hit in frame %d.\n", entry->frame_id);
            entry->PageFault = FALSE;
            return entry;
        }
    }
    
    // otherwise, lets make a new frame entry
    entry2 = frame_entry_new();
    entry2->cpu_time = cpu_time;
    entry2->last_used = 0;
    entry2->page = page;
    entry2->empty = FALSE;
    entry2->process_id = process_id;
    
    // and insert it in a blank slot if there is one
    for (i = ft->count - 1; i >= 0; i--) {
        entry3 = ft->framelist[i];
        assert(entry3 != NULL);
        if (entry3->empty) {
            assert(entry2 != NULL);
            entry2->frame_id = i;
            ft->framelist[entry2->frame_id] = entry2;
            process *process1 = ProcessArray[process_id - 1];
            assert(process1 != NULL);
            process1->PageFaults++;
            entry2->PageFault = TRUE;
            printf("Fault, using free frame %d.\n", entry2->frame_id);
            return entry2;
        }
    }
    
    // otherwise we're going to pick a victim frame to evict
    assert(ft != NULL);                     // Here we're
    assert(ft->framelist != NULL);          // just grabbing
    assert(ft->count > 0);                  // the first
    entry3 = ft->framelist[ft->count - 1];  // frame entry
    assert(entry3 != NULL);                 // from the 
    int least_cpu_time = entry3->cpu_time;  // frame list
    int frame_to_evict = entry3->frame_id;  // 
    
    int j; // Now loop through all the frames looking for the one with the minimum cpu_time
    for (j = ft->count - 2; j >= 0; j--) {
        assert(j >= 0);
        entry3 = ft->framelist[j]; // grab the next one
        if (entry3->cpu_time < least_cpu_time) { // we're trying to find the min cpu time
            least_cpu_time = entry3->cpu_time;
            frame_to_evict = entry3->frame_id;
        }
    }
    entry2->frame_id = frame_to_evict;                       // let our new frame entry move in
    entry3 = ft->framelist[frame_to_evict];                  // this is the frame entry that's moving out
    process3 = ProcessArray[entry3->process_id - 1];         // this is the process that's moving out
    process3->TotalResidency += cpu_time - entry3->cpu_time; // update his residency time
    process3->Evicted++;                                     // increment his evection status
    ft->framelist[frame_to_evict] = entry2;                  // move our new frame entry in
    process2 = ProcessArray[process_id - 1];                 // this is the process that's moving in
    assert(process2 != NULL);                                // this process shouldn't be null
    process2->PageFaults++;                                  // increment the incoming process' pagefault count
    entry2->PageFault = TRUE;                                // yes, we had a page fault
    printf("Fault, evicting page %d of %d from frame %d.\n", \
        entry3->page, process3->ID, entry3->frame_id);
    return entry2;
}

frame_entry *simulate_lru(frame_table *ft, int page, int cpu_time, int process_id)
{
    frame_entry *entry2 = NULL;
    frame_entry *entry3 = NULL;
    process *process2 = NULL;
    process *process3 = NULL;
    int i;
    
    // if the given page is already in the frame table, go ahead and use it.
    for(i = ft->count - 1; i >= 0; i--) {
        frame_entry *entry = ft->framelist[i];
        assert(entry != NULL);
        if ((!entry->empty && (entry->page == page)) && (entry->process_id == process_id)) {
            printf("Hit in frame %d.\n", entry->frame_id);
            entry->last_used = cpu_time;
            entry->PageFault = FALSE;
            return entry;
        }
    }
    
    // otherwise, lets make a new frame entry
    entry2 = frame_entry_new();
    entry2->cpu_time = cpu_time;
    entry2->last_used = cpu_time;
    entry2->page = page;
    entry2->empty = FALSE;
    entry2->process_id = process_id;
    
    // and insert it in a blank slot if there is one
    for (i = ft->count - 1; i >= 0; i--) {
        entry3 = ft->framelist[i];
        assert(entry3 != NULL);
        if (entry3->empty) {
            assert(entry2 != NULL);
            entry2->frame_id = i;
            ft->framelist[entry2->frame_id] = entry2;
            process *process1 = ProcessArray[process_id - 1];
            assert(process1 != NULL);
            process1->PageFaults++;
            entry2->PageFault = TRUE;
            printf("Fault, using free frame %d.\n", entry2->frame_id);
            return entry2;
        }
    }
    
    // otherwise we're going to pick a victim frame to evict
    assert(ft != NULL);                     // Here we're
    assert(ft->framelist != NULL);          // just grabbing
    assert(ft->count > 0);                  // the first
    entry3 = ft->framelist[ft->count - 1];  // frame entry
    assert(entry3 != NULL);                 // from the 
    int least_cpu_time = entry3->cpu_time;  // frame list
    int frame_to_evict = entry3->frame_id;  // 
    
    int j; // Now loop through all the frames looking for the one with the minimum last_used
    for (j = ft->count - 2; j >= 0; j--) {
        assert(j >= 0);
        entry3 = ft->framelist[j]; // grab the next one
        if (entry3->last_used < least_cpu_time) { // we're trying to find the min last_used
            least_cpu_time = entry3->last_used;
            frame_to_evict = entry3->frame_id;
        }
    }
    entry2->frame_id = frame_to_evict;                       // let our new frame entry move in
    entry3 = ft->framelist[frame_to_evict];                  // this is the frame entry that's moving out
    process3 = ProcessArray[entry3->process_id - 1];         // this is the process that's moving out
    process3->TotalResidency += cpu_time - entry3->cpu_time; // update his residency time
    process3->Evicted++;                                     // increment his evection status
    ft->framelist[frame_to_evict] = entry2;                  // move our new frame entry in
    process2 = ProcessArray[process_id - 1];                 // this is the process that's moving in
    assert(process2 != NULL);                                // this process shouldn't be null
    process2->PageFaults++;                                  // increment the incoming process' pagefault count
    entry2->PageFault = TRUE;                                // yes, we had a page fault
    printf("Fault, evicting page %d of %d from frame %d.\n", \
        entry3->page, process3->ID, entry3->frame_id);
    return entry2;
}
