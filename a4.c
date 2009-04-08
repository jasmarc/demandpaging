#include "a4.h"

int main (int argc, char *argv[])
{
    char *subopts, *value;
    int opt,
	machine_size   = 0,
        page_size      = 0,
	process_size   = 0,
	job_mix        = 0,
	number_of_refs = 0,
	fifo           = 0,
        clock          = 0,
	lru            = 0,
	no_pager       = 1;
    char *filename     = NULL;

    if(argc == 1) {
        print_usage(argc, argv);
        return 1;
    }
    while((opt = getopt(argc, argv, "hvn:i:s:")) != -1)
        switch(opt)
    {
        case 'h':
            print_usage(argc, argv);
            break;
        case 'm':
	    machine_size = atoi(optarg);
            break;
        case 'p':
	    page_size = atoi(optarg);
            break;
        case 's':
	    process_size = atoi(optarg);
            break;
        case 'j':
	    job_mix = atoi(optarg);
            break;
        case 'n':
            number_of_refs = atoi(optarg);
            break;
        case 'r':
            subopts = optarg;
            while(*subopts != '\0')
                switch(getsubopt(&subopts, pager_opts, &value))
            {
                case FIFO:
                    fifo = 1;
                    break;
                case CLOCK:
                    clock = 1;
                    break;
                case LRU:
                    lru = 1;
                    break;
                default:
                    printf("unknown pager passed in list to -s\n");
                    break;
            }
            no_pager = 0;
            break;
        default:
            print_usage(argc, argv);
            abort();
            break;
    }
    
    printf("m = %d\n", machine_size);
    printf("p = %d\n", page_size);
    printf("s = %d\n", process_size);
    printf("j = %d\n", job_mix);
    printf("n = %d\n", number_of_refs);
    printf("fifo  = %d\n", fifo);
    printf("clock = %d\n", clock);
    printf("lru   = %d\n", lru);

    return 0;
}

// public FrameEntry simulate_fifo(Environment env, int page, int cpu_time, int process_id)
// {
//     FrameEntry entry3;
//     foreach (FrameEntry entry in this.FrameList)
//     {
//         if ((!entry.empty && (entry.page == page)) && (entry.process_id == process_id))
//         {
//             entry.PageFault = false;
//             return entry;
//         }
//     }
//     FrameEntry entry2 = new FrameEntry();
//     entry2.cpu_time = cpu_time;
//     entry2.last_used = 0;
//     entry2.page = page;
//     entry2.empty = false;
//     entry2.process_id = process_id;
//     for (int i = this.FrameList.get_Count() - 1; i >= 0; i--)
//     {
//         entry3 = this.FrameList.get_Item(i);
//         if (entry3.empty)
//         {
//             entry2.frame_id = i;
//             this.FrameList.set_Item(entry2.frame_id, entry2);
//             Process process1 = env.GetProcess(process_id);
//             process1.PageFaults++;
//             entry2.PageFault = true;
//             return entry2;
//         }
//     }
//     entry3 = this.FrameList.get_Item(this.FrameList.get_Count() - 1);
//     int num2 = entry3.cpu_time;
//     int num3 = entry3.frame_id;
//     for (int j = this.FrameList.get_Count() - 2; j >= 0; j--)
//     {
//         entry3 = this.FrameList.get_Item(j);
//         if (entry3.cpu_time < num2)
//         {
//             num2 = entry3.cpu_time;
//             num3 = entry3.frame_id;
//         }
//     }
//     entry2.frame_id = num3;
//     entry3 = this.FrameList.get_Item(num3);
//     Process process = env.GetProcess(entry3.process_id);
//     process.TotalResidency += cpu_time - entry3.cpu_time;
//     process.Evicted++;
//     this.FrameList.set_Item(num3, entry2);
//     Process process2 = env.GetProcess(process_id);
//     process2.PageFaults++;
//     entry2.PageFault = true;
//     return entry2;
// }

// public void Run()
// {
//     this.GetRandomNumbers("random-numbers");
//     int num = 1;
//     double num2 = 0.0;
//     int nextReference = -1;
//     int num5 = 0;
//     this.frame_table = new FrameTable(this.MachineSize / this.PageSize);
//     while (this.RunningQueue.get_Count() > 0)
//     {
//         Process p = this.RunningQueue.Peek();
//         for (int i = 0; i < this.Quantum; i++)
//         {
//             if (p.NumberOfReferences == this.NumberOfReferences)
//             {
//                 nextReference = (0x6f * p.ID) % this.SizeOfProcess;
//             }
//             if (p.NextReference != -1)
//             {
//                 nextReference = p.NextReference;
//                 p.NextReference = -1;
//             }
//             p.CurrentReference = nextReference;
//             FrameEntry entry = null;
//             if (this.ReplacementAlgorithim == Algorithim.FIFO)
//             {
//                 entry = this.frame_table.simulate_fifo(this, this.GetPage(p.CurrentReference), num, p.ID);
//             }
//             else if (this.ReplacementAlgorithim == Algorithim.LRU)
//             {
//                 entry = this.frame_table.simulate_lru(this, this.GetPage(p.CurrentReference), num, p.ID);
//             }
//             else if (this.ReplacementAlgorithim == Algorithim.Random)
//             {
//                 entry = this.frame_table.simulate_random(this, this.GetPage(p.CurrentReference), num, p.ID);
//             }
//             if (entry.PageFault)
//             {
//                 num5++;
//             }
//             p.NumberOfReferences--;
//             num2 = this.GetNextRandom() / 2147483648;
//             if (num2 < p.A)
//             {
//                 nextReference = (p.CurrentReference + 1) % this.SizeOfProcess;
//             }
//             else if (num2 < (p.A + p.B))
//             {
//                 nextReference = ((p.CurrentReference - 5) + this.SizeOfProcess) % this.SizeOfProcess;
//             }
//             else if (num2 < ((p.A + p.B) + p.C))
//             {
//                 nextReference = (p.CurrentReference + 4) % this.SizeOfProcess;
//             }
//             else if (num2 >= ((p.A + p.B) + p.C))
//             {
//                 int nextRandom = this.GetNextRandom();
//                 nextReference = nextRandom % this.SizeOfProcess;
//             }
//             num++;
//             if (this.CanTerminate(p))
//             {
//                 break;
//             }
//         }
//         p.NextReference = nextReference;
//         this.RunningQueue.Dequeue();
//         if (!this.CanTerminate(p))
//         {
//             this.RunningQueue.Enqueue(p);
//             this.Quantum = 3;
//         }
//     }
//     this.Print_Result();
// }
