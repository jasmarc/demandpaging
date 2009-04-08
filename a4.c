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
    GetRandomNumbers(filename);
    int num = 1;
    double num2 = 0->0;
    int nextReference = -1;
    int num5 = 0;
    frame_entry *frame_table[MachineSize / PageSize];
    while (RunningQueue->get_Count() > 0)
    {
        Process p = RunningQueue->Peek();
        for (int i = 0; i < Quantum; i++)
        {
            if (p->NumberOfReferences == NumberOfReferences) {
                nextReference = (0x6f * p->ID) % SizeOfProcess;
            }
            if (p->NextReference != -1) {
                nextReference = p->NextReference;
                p->NextReference = -1;
            }
            p->CurrentReference = nextReference;
            frame_entry *entry = NULL;
            switch(ReplacementAlgorithim)
            {
                case FIFO:
                    entry = simulate_fifo(frame_table, GetPage(p->CurrentReference), num, p->ID);
                    break;
                case CLOCK:
                    entry = simulate_random(frame_table, GetPage(p->CurrentReference), num, p->ID);
                    break;
                case LRU:
                    entry = simulate_lru(frame_table, GetPage(p->CurrentReference), num, p->ID);
                    break;
                default:
                    // todo: error handling
                    break;
            }
            if (entry->PageFault)
            {
                num5++;
            }
            p->NumberOfReferences--;
            num2 = GetNextRandom() / 2147483648;
            if (num2 < p->A) {
                nextReference = (p->CurrentReference + 1) % SizeOfProcess;
            }
            else if (num2 < (p->A + p->B)) {
                nextReference = ((p->CurrentReference - 5) + SizeOfProcess) % SizeOfProcess;
            }
            else if (num2 < ((p->A + p->B) + p->C)) {
                nextReference = (p->CurrentReference + 4) % SizeOfProcess;
            }
            else if (num2 >= ((p->A + p->B) + p->C)) {
                int nextRandom = GetNextRandom();
                nextReference = nextRandom % SizeOfProcess;
            }
            num++;
            if (CanTerminate(p)) {
                break;
            }
        }
        p->NextReference = nextReference;
        RunningQueue->Dequeue();
        if (!CanTerminate(p))
        {
            RunningQueue->Enqueue(p);
            Quantum = 3;
        }
    }
    Print_Result();
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
            // todo: handle error here
            break;
    }
    // todo: enqueue processes here
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
