#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "heap.h"

#define TRUE  1
#define FALSE 0

typedef struct {
    int id,         // the id of the job
        arrive,     // the arrive time
        burst,      // the remaining burst time
        waiting,    // the cumulative wait time
        start,      // the start time
        end,        // the end time
        priority,   // the priority of the job
        service;    // most recent service time
} job;

// Pager Algorithms (used by getopts parser)
enum {
  FIFO = 0,
  CLOCK,
  LRU,
  THE_END
};
// Pager Algorithms (used by getopts parser)
char *pager_opts[] = {
  [FIFO]    = "fifo",
  [CLOCK]   = "clock",
  [LRU]     = "lru",
  [THE_END] = NULL

};

// print the command line usage
void print_usage(int argc, char *argv[])
{
    printf("usage:\t\t%s [OPTIONS]\n", argv[0]);
    printf("example:\t%s -i data.txt -s sjf,fcfs,srtf -v\n", argv[0]);
    printf("\t\t%s -n 5 -s sjf\n", argv[0]);
    printf("options:\n");
    printf(" -h\t\tPrint this message.\n");
    printf(" -i <file>\tRead comma-separated file with arrive,burst\n");
    printf(" -n <number>\tNumber of jobs to generate if not reading from file.\n");
    printf(" -s <sched(s)>\tSpecify pager(s) to use.\n");
    printf(" \t\tValid pagers are: sjf, fcfs, srtf, rr, unix\n");
    printf(" -v\t\tVerbose mode. Prints an output for each CPU cycle.\n");
    return;
}
