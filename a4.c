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
    char *filename = NULL;

    if(argc == 1) {
        print_usage(argc, argv);
        return 1;
    }
    while((opt = getopt(argc, argv, "hi:m:p:s:j:n:r:")) != -1)
        switch(opt)
    {
        case 'h':
            print_usage(argc, argv);
            break;
        case 'i':
            filename = malloc(sizeof(optarg));
            strcpy(filename, optarg);
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
                    printf("unknown pager passed in list to -r\n");
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
    printf("filename = %s\n", filename);

    return 0;
}

void run()
{
/*     this.GetRandomNumbers("random-numbers");
    int num = 1;
    double num2 = 0.0;
    int nextReference = -1;
    int num5 = 0;
    this.frame_table = new FrameTable(this.MachineSize / this.PageSize);
    while (this.RunningQueue.get_Count() > 0)
    {
        Process p = this.RunningQueue.Peek();
        for (int i = 0; i < this.Quantum; i++)
        {
            if (p.NumberOfReferences == this.NumberOfReferences)
            {
                nextReference = (0x6f * p.ID) % this.SizeOfProcess;
            }
            if (p.NextReference != -1)
            {
                nextReference = p.NextReference;
                p.NextReference = -1;
            }
            p.CurrentReference = nextReference;
            FrameEntry entry = null;
            if (this.ReplacementAlgorithim == Algorithim.FIFO)
            {
                entry = this.frame_table.simulate_fifo(this, this.GetPage(p.CurrentReference), num, p.ID);
            }
            else if (this.ReplacementAlgorithim == Algorithim.LRU)
            {
                entry = this.frame_table.simulate_lru(this, this.GetPage(p.CurrentReference), num, p.ID);
            }
            else if (this.ReplacementAlgorithim == Algorithim.Random)
            {
                entry = this.frame_table.simulate_random(this, this.GetPage(p.CurrentReference), num, p.ID);
            }
            if (entry.PageFault)
            {
                num5++;
            }
            p.NumberOfReferences--;
            num2 = this.GetNextRandom() / 2147483648;
            if (num2 < p.A)
            {
                nextReference = (p.CurrentReference + 1) % this.SizeOfProcess;
            }
            else if (num2 < (p.A + p.B))
            {
                nextReference = ((p.CurrentReference - 5) + this.SizeOfProcess) % this.SizeOfProcess;
            }
            else if (num2 < ((p.A + p.B) + p.C))
            {
                nextReference = (p.CurrentReference + 4) % this.SizeOfProcess;
            }
            else if (num2 >= ((p.A + p.B) + p.C))
            {
                int nextRandom = this.GetNextRandom();
                nextReference = nextRandom % this.SizeOfProcess;
            }
            num++;
            if (this.CanTerminate(p))
            {
                break;
            }
        }
        p.NextReference = nextReference;
        this.RunningQueue.Dequeue();
        if (!this.CanTerminate(p))
        {
            this.RunningQueue.Enqueue(p);
            this.Quantum = 3;
        }
    }
    this.Print_Result(); */
}

void SetJobMix(int j)
{
    process *processes[4];
    int NumberOfProcesses; // todo: move this
    int NumberOfReferences = 0; // todo: move this
    switch(j)
    {
        case 1:
            NumberOfProcesses = 1;
            process_new(processes[0], 1, 1.0, 0.0, 0.0, NumberOfReferences);
            break;
        case 2:
            NumberOfProcesses = 4;
            process_new(processes[0], 1, 1.0, 0.0, 0.0, NumberOfReferences);
            process_new(processes[1], 2, 1.0, 0.0, 0.0, NumberOfReferences);
            process_new(processes[2], 3, 1.0, 0.0, 0.0, NumberOfReferences);
            process_new(processes[3], 4, 1.0, 0.0, 0.0, NumberOfReferences);
            break;
        case 3:
            NumberOfProcesses = 4;
            process_new(processes[0], 1, 0.0, 0.0, 0.0, NumberOfReferences);
            process_new(processes[1], 2, 0.0, 0.0, 0.0, NumberOfReferences);
            process_new(processes[2], 3, 0.0, 0.0, 0.0, NumberOfReferences);
            process_new(processes[3], 4, 0.0, 0.0, 0.0, NumberOfReferences);
            break;
        case 4:
            NumberOfProcesses = 4;
            process_new(processes[0], 1, 0.75, 0.25, 0.0, NumberOfReferences);
            process_new(processes[1], 2, 0.75, 0.0, 0.25, NumberOfReferences);
            process_new(processes[2], 3, 0.75, 0.125, 0.125, NumberOfReferences);
            process_new(processes[3], 4, 0.5, 0.125, 0.125, NumberOfReferences);
            break;
        default:
            // handle error here
            break;
    }
}
 
void GetRandomNumbers(heap *h, int (*comp_func)(void*, void*), char *filename)
{
    char buffer[256];
    FILE *fp = NULL;
    if((fp = fopen(filename, "r"))) {
        while (!feof(fp)) {
            fgets(buffer, 256, fp); // read a line
 
            // tokenize the line by commas and newlines
/*             if(strlen(buffer) > 1) {
                if((temp = strtok(buffer, ",\n")) != NULL && strlen(temp) > 0)
                    arrive += strtol(temp, NULL, 10);
                if((temp = strtok(NULL, ",\n")) != NULL && strlen(temp) > 0)
                    burst = strtol(temp, NULL, 10);
                job *temp = malloc(sizeof(job)); // create a new job
                build_job(temp, i++, arrive, burst); // populate it
                heap_insert(h, comp_func, temp); // stick it in the queue
            } */
            printf("%s", buffer);
        }
        fclose(fp);
    }
    else {
        fprintf(stderr, "error opening file %s\n", filename);
        exit(1);
    }
    return;
}
