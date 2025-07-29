#include <stdio.h>
#include "fifo.h"

void fifo_schedule(Process processes[], int num_processes)
{
    int current_time = 0;
    
    for (int i = 0; i < num_processes; i++)
    {
        if (current_time < processes[i].arrival_time)
        {
            printf("[Time %d] CPU is idle.\n", current_time);
            current_time = processes[i].arrival_time;
        }

        while (processes[i].remaining_burst_time > 0)
        {
            printf("[Time %d] %s is running (Remaining: %d)\n", current_time, processes[i].pid, processes[i].remaining_burst_time);
            processes[i].remaining_burst_time--;
            current_time++;
        }
        printf("[Time %d] %s finished execution.\n", current_time, processes[i].pid);
    }
}
