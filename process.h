#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    double A;
    double B;
    double C;
    int CurrentReference;
    int Evicted;
    int ID;
    int NextReference;
    int NumberOfReferences;
    int PageFaults;
    int Random;
    int Terminated;
    int TotalResidency;
} process;

process *process_new(int ID, double A, double B, double C, int R);

#endif /* PROCESS_H */
