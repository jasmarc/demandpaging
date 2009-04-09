#include "a4.h"
#include "assert.h"

int machine_size   = 0,
    page_size      = 0,
    process_size   = 0,
    job_mix        = 0,
    number_of_refs = 0,
    fifo           = 0,
    clock          = 0,
    lru            = 0,
    algorithm      = 0,
    no_pager       = 1;
char *filename = NULL;
extern process *ProcessArray[4];
int NumberOfProcesses;
fifo_queue *RunningQueue;
fifo_queue *RandomNumbers;

int main (int argc, char *argv[])
{
    char *subopts, *value;
    int opt;

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
                switch(algorithm = getsubopt(&subopts, pager_opts, &value))
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
    
    printf("The machine size is %d.\n", machine_size);
    printf("The page size is %d.\n", page_size);
    printf("The process size is %d.\n", process_size);
    printf("The job mix numbmer is %d.\n", job_mix);
    printf("The number of references per process is %d.\n", number_of_refs);
    switch(algorithm)
    {
        case FIFO:
            printf("The replacement algorithm is fifo.\n");
            break;
        case CLOCK:
            printf("The replacement algorithm is clock.\n");
            break;
        case LRU:
            printf("The replacement algorithm is lru.\n");
            break;
        default:
            // todo: error handling
            break;
    }
    printf("filename = %s\n", filename);
    printf("set job mix\n");
    SetJobMix(job_mix);
    printf("run\n");
    run();
    printf("done\n");
    return 0;
}

void run()
{
    int num = 1;
    double num2 = 0.0;
    int nextReference = -1;
    int num5 = 0;
    int i = 0;
    int Quantum = 3;
    frame_table *ft = frame_table_new(machine_size / page_size);
    
    GetRandomNumbers(filename);
    process *p = NULL;
    while (p = peek(RunningQueue))
    {
        assert(p != NULL);
        for (i = 0; i < Quantum; i++)
        {
            if (p->NumberOfReferences == number_of_refs) {
                nextReference = (111 * p->ID) % process_size;
            }
            if (p->NextReference != -1) {
                nextReference = p->NextReference;
                p->NextReference = -1;
            }
            p->CurrentReference = nextReference;
            frame_entry *entry = NULL;
            printf("%d references word %d (page %d) at time %d: ", \
                p->ID, p->CurrentReference, p->CurrentReference / page_size, num);
            switch(algorithm)
            {
                case FIFO:
                    entry = simulate_fifo(ft, p->CurrentReference / page_size, num, p->ID);
                    break;
                // case CLOCK:
                //     entry = simulate_random(frame_table, GetPage(p->CurrentReference), num, p->ID);
                //     break;
                // case LRU:
                //     entry = simulate_lru(frame_table, GetPage(p->CurrentReference), num, p->ID);
                //     break;
                default:
                    // todo: error handling
                    break;
            }
            if (entry->PageFault) {
                num5++;
            }
            p->NumberOfReferences--;
            num2 = GetNextRandomNumber() / 2147483648;
            if (num2 < p->A) {
                nextReference = (p->CurrentReference + 1) % process_size;
            }
            else if (num2 < (p->A + p->B)) {
                nextReference = ((p->CurrentReference - 5) + process_size) % process_size;
            }
            else if (num2 < ((p->A + p->B) + p->C)) {
                nextReference = (p->CurrentReference + 4) % process_size;
            }
            else if (num2 >= ((p->A + p->B) + p->C)) {
                int nextRandom = GetNextRandomNumber();
                nextReference = nextRandom % process_size;
            }
            num++;
            if (p->NumberOfReferences == 0) {
                break;
            }
        }
        p->NextReference = nextReference;
        dequeue(RunningQueue);
        if (p->NumberOfReferences != 0)
        {
            enqueue(RunningQueue, p);
            Quantum = 3;
        }
    }
    // Print_Result();
}

void SetJobMix(int j)
{
    switch(j)
    {
        case 1:
            NumberOfProcesses = 1;
            ProcessArray[0] = process_new(1, 1.0, 0.0, 0.0, number_of_refs);
            break;
        case 2:
            NumberOfProcesses = 4;
            ProcessArray[0] = process_new(1, 1.0, 0.0, 0.0, number_of_refs);
            ProcessArray[1] = process_new(2, 1.0, 0.0, 0.0, number_of_refs);
            ProcessArray[2] = process_new(3, 1.0, 0.0, 0.0, number_of_refs);
            ProcessArray[3] = process_new(4, 1.0, 0.0, 0.0, number_of_refs);
            break;
        case 3:
            NumberOfProcesses = 4;
            ProcessArray[0] = process_new(1, 0.0, 0.0, 0.0, number_of_refs);
            ProcessArray[1] = process_new(2, 0.0, 0.0, 0.0, number_of_refs);
            ProcessArray[2] = process_new(3, 0.0, 0.0, 0.0, number_of_refs);
            ProcessArray[3] = process_new(4, 0.0, 0.0, 0.0, number_of_refs);
            break;
        case 4:
            NumberOfProcesses = 4;
            ProcessArray[0] = process_new(1, 0.75, 0.25, 0.0, number_of_refs);
            ProcessArray[1] = process_new(2, 0.75, 0.0, 0.25, number_of_refs);
            ProcessArray[2] = process_new(3, 0.75, 0.125, 0.125, number_of_refs);
            ProcessArray[3] = process_new(4, 0.5, 0.125, 0.125, number_of_refs);
            break;
        default:
            // todo: handle error here
            break;
    }
    RunningQueue = fifo_queue_new();
    int i;
    for(i = 0; i < NumberOfProcesses; ++i) {
        enqueue(RunningQueue, ProcessArray[i]);
    }
}
 
void GetRandomNumbers(char *filename)
{
    printf("GetRandomNumbers\n");
    char buffer[256];
    FILE *fp = NULL;
    if((fp = fopen(filename, "r"))) {
        RandomNumbers = fifo_queue_new();
        while (!feof(fp)) {
            fgets(buffer, 256, fp); // read a line
            if(strlen(buffer) > 1) {
                int *val = malloc(sizeof(int));
                *val = strtol(buffer, NULL, 10);
                enqueue(RandomNumbers, val);
            }
        }
        fclose(fp);
    }
    else {
        fprintf(stderr, "error opening file %s\n", filename);
        exit(1);
    }
    return;
}

int GetNextRandomNumber()
{
    int *val = dequeue(RandomNumbers);
    return val != NULL ? *val : -1;
}

// print the command line usage
void print_usage(int argc, char *argv[])
{
    printf("usage:\t\t%s [OPTIONS]\n", argv[0]);
    printf("example:\t%s -m9 -p3 -s3 -j4 -n5 -r fifo -i input.txt\n", argv[0]);
    printf("options:\n");
    printf(" -h\t\tPrint this message.\n");
    printf(" -i <file>\tRead comma-separated file with arrive,burst\n");
    printf(" -m\t\tThe machine size (in words)\n");
    printf(" -p\t\tThe page size (in words)\n");
    printf(" -s\t\tThe size of a processes\n");
    printf(" -j\t\tThe 'job mix'\n");
    printf(" -n\t\tThe number of simulated references for each process\n");
    printf(" -r <pager(s)>\tSpecify pager(s) to use.\n");
    printf(" \t\tValid pagers are: fifo, clock, lru\n");
    return;
}
