#include <stdio.h>
#include <string.h>
#include "fifo.h"
#include "sjf.h"
#include "rr.h"  // future addition

#define NUM_PROCESSES 3

int main(int argc, char* argv[])
{
    
    //* default algorithm
    char *algorithm = "FIFO";      
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--algorithm") == 0) {
            algorithm = argv[++i];
        }
    }
    
    
    Process processes[NUM_PROCESSES] = { {"P1", 0, 5, 0}, {"P2", 6, 3, 0}, {"P3", 6, 2, 0} };


    if (strcmp(algorithm, "FIFO") == 0)
        fifo_schedule(processes, NUM_PROCESSES);
    else if (strcmp(algorithm, "SJF") == 0)
        sjf_schedule(processes, NUM_PROCESSES);
    // else if (strcmp(algorithm, "RR") == 0)
    //     rr_schedule(processes, NUM_PROCESSES, 2);  // Example quantum
    else
        printf("Unknown scheduling algorithm.\n");

    return 0;
}
