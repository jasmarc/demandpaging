#include "heap.h"
#include "fifo.h"
#include "frametable.h"
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

int fcfs_process_comparison(void *a, void *b);
void GetRandomNumbers(char *filename);
int GetNextRandomNumber();
void Print_Result();
void print_usage(int argc, char *argv[]);
void run();
void SetJobMix(int j);
