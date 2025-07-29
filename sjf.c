#include <stdio.h>
#include "sjf.h"

int find_shortest_arrived_process(Process processes[], int num_processes, int current_time)
{
    int shortest_process_index = -1;
    int min_remaining_burst_time = __INT_MAX__;

    for(int i = 0; i < num_processes; i++)
    {
        if(processes[i].remaining_burst_time < min_remaining_burst_time && processes[i].completed_flag == 0 && processes[i].arrival_time <= current_time)
        {
            shortest_process_index = i;
            min_remaining_burst_time = processes[i].remaining_burst_time;
        }
    }

    return shortest_process_index;
}

int find_nearest_arriving_process(Process processes[], int num_processes, int current_time)
{
    int nearest_index = -1;
    int min_diff = __INT_MAX__;
    
    for(int i = 0; i < num_processes; i++)
    {
        int diff =  processes[i].arrival_time - current_time;

        if(diff < min_diff && processes[i].completed_flag == 0)
        {
            min_diff = diff;
            nearest_index = i;
        }
    }

    // not very much needed
    if(nearest_index == -1)
    {
        printf("Some error");
        return 1;
    }

    return nearest_index;

}

void sjf_schedule(Process processes[], int num_processes)
{
    int current_time = 0;

    int completed = 0;  // keeping count of completed processes

     while (completed < num_processes) {



        // Find shortest job among arrived processes
        int shortest_idx = find_shortest_arrived_process(processes, num_processes, current_time);

        if(shortest_idx == -1)
        {
            int nearest_idx = find_nearest_arriving_process(processes, num_processes, current_time);
            // skip current time to the very next arriving process' arrival time
            printf("CPU idle from %d to %d\n", current_time, processes[nearest_idx].arrival_time);
            current_time = processes[nearest_idx].arrival_time;
            continue;

        }
        
        // Run it to completion
        while (processes[shortest_idx].remaining_burst_time > 0)
        {
            printf("[Time %d] %s is running (Remaining: %d)\n", current_time, processes[shortest_idx].pid, processes[shortest_idx].remaining_burst_time);
            processes[shortest_idx].remaining_burst_time--;
            current_time++;
        }

        // Mark as completed
        processes[shortest_idx].completed_flag = 1;
        completed++; // marking that one (more) process has completed its execution
    }



}
