#include "process.h"

void process_new(process *p, int ID, double A, double B, double C, int R)
{
    p = malloc(sizeof(process));
    p->A                  = A;
    p->B                  = B;
    p->C                  = C;
    p->CurrentReference   = 0;
    p->Evicted            = 0;
    p->ID                 = ID;
    p->NextReference      = -1;
    p->NumberOfReferences = R;
    p->PageFaults         = 0;
    p->Random             = 0;
    p->Terminated         = FALSE;
    p->TotalResidency     = 0;
    return;
}
