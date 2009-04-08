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
    bool Terminated;
    int TotalResidency;
} process;

void process_new(process *p)
{
    p = malloc(sizeof(process));
    p->A                  = 0;
    p->B                  = 0;
    p->C                  = 0;
    p->CurrentReference   = 0;
    p->Evicted            = 0;
    p->ID                 = 0;
    p->NextReference      = 0;
    p->NumberOfReferences = 0;
    p->PageFaults         = 0;
    p->Random             = 0;
    p->Terminated         = FALSE;
    p->TotalResidency     = 0;
    return;
}