#include <stdlib.h>
#define TRUE 1
#define FALSE 0

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

void process_new(process *p, int ID, double A, double B, double C, int R);
