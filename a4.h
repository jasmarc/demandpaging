#include "heap.h"
#include "process.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE  1
#define FALSE 0

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
    printf("example:\t%s -i data.txt -m1 -p2 -s3 -j4 -n5 -r fifo\n", argv[0]);
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
