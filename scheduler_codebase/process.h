#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process
{
    char *pid;
    int arrival_time;
    int remaining_burst_time;
    int completed_flag; // to identify if a particular process is completed or not 
} Process;

#endif
