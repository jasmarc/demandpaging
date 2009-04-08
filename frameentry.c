#include "frameentry.h"

void frame_entry_new(frame_entry *f)
{
    f = malloc(sizeof(frame_entry));
    f->cpu_time  = 0;
    f->empty     = FALSE;
    f->frame_id  = 0;
    f->last_used = 0;
    f->page      = 0;
    f->PageFault = FALSE;
    f->process_id= 0;
    return;
}

// public FrameEntry simulate_fifo(int page, int cpu_time, int process_id)
// {
    // FrameEntry entry3;
    // foreach (FrameEntry entry in this.FrameList)
    // {
        // if ((!entry.empty && (entry.page == page)) && (entry.process_id == process_id))
        // {
            // entry.PageFault = false;
            // return entry;
        // }
    // }
    // FrameEntry entry2 = new FrameEntry();
    // entry2.cpu_time = cpu_time;
    // entry2.last_used = 0;
    // entry2.page = page;
    // entry2.empty = false;
    // entry2.process_id = process_id;
    // for (int i = this.FrameList.get_Count() - 1; i >= 0; i--)
    // {
        // entry3 = this.FrameList.get_Item(i);
        // if (entry3.empty)
        // {
            // entry2.frame_id = i;
            // this.FrameList.set_Item(entry2.frame_id, entry2);
            // Process process1 = env.GetProcess(process_id);
            // process1.PageFaults++;
            // entry2.PageFault = true;
            // return entry2;
        // }
    // }
    // entry3 = this.FrameList.get_Item(this.FrameList.get_Count() - 1);
    // int num2 = entry3.cpu_time;
    // int num3 = entry3.frame_id;
    // for (int j = this.FrameList.get_Count() - 2; j >= 0; j--)
    // {
        // entry3 = this.FrameList.get_Item(j);
        // if (entry3.cpu_time < num2)
        // {
            // num2 = entry3.cpu_time;
            // num3 = entry3.frame_id;
        // }
    // }
    // entry2.frame_id = num3;
    // entry3 = this.FrameList.get_Item(num3);
    // Process process = env.GetProcess(entry3.process_id);
    // process.TotalResidency += cpu_time - entry3.cpu_time;
    // process.Evicted++;
    // this.FrameList.set_Item(num3, entry2);
    // Process process2 = env.GetProcess(process_id);
    // process2.PageFaults++;
    // entry2.PageFault = true;
    // return entry2;
// }
