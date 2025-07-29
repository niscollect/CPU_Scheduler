**Scheduler Simulator**  - a program that **mimics how an OS schedules CPU time to multiple processes**, using algorithms like FIFO, SJF, or Round Robin.

It’s not a real OS kernel. It’s a simulation that **runs tick by tick** (1 tick = 1 time unit), tracking:

- Which process is running
    
- Which are waiting
    
- Which are doing I/O
    
- And how they move between these states

Think of it as a **time-driven OS lab in code**.

<hr>
The program:

1. **Reads a list of processes** (arrival time, CPU & I/O bursts)
    
2. **Simulates a CPU scheduler** (FIFO, SJF, etc.)
    
3. **Output**:
    
    - A timeline of which process ran when
        
    - Metrics like turnaround time, response time, waiting time
        
    - Per-process breakdowns

<hr>
<hr>

# Building log:-
#buildLog
### Step 0: The Minimal Working Setup

Goal:

Write a **simple main program** that:
- Can read a **dummy process line** like `P1 0 4,5,6 2,3`
- Creates a `Process` struct in memory
- Prints it out

That's it. Don’t simulate anything yet.

So, for this, let's go intuitively. 
- First, we'll need a process, for which we'll need struct
- Some way to represent “running”, which means we need a variable or state
- We'll need to advance and keep track of time, so a variable for that as well
- And eventually print at the end

The very basic understanding code:

```c
	// process structure
	typedef struct Process{
	    char* pid; // process's identification
	    int arrival_time;
	    int remaining_burst_time;    
	} Process;
	
	int main()
	{
	    Process p = {"P1", 0, 5};   // A process that needs 5 ticks of CPU

	    // To keep track of the global CPU time
	    int current_time = 0;
	
	    // loop through the process
	    while (p.remaining_burst_time > 0) {
		       printf("[Time %d] %s is running (Remaining: %d)\n", current_time, p.pid, p.remaining_burst_time);
		       p.remaining_burst_time--;
		       current_time++;
	    }
	    printf("[Time %d] %s finished execution.\n", current_time, p.pid);
	    return 0;
	}
```


### Step 1: Adding Multiple processes

Simulate **multiple processes** being executed one by one — like a CPU running them **in order** of their arrival (no fancy scheduling yet, just FCFS-like idea).

So....
How does it go? :
We imagine a queue of processes. The CPU:
1. Starts at `current_time = 0`
2. Looks for the next process that has `arrival_time <= current_time`
3. Runs it till its `remaining_burst_time` is 0
4. Then moves to the next such process


The very basic implementation:
```c	
 #include <stdio.h>
	//* process structure

	typedef struct Process
	{
		    char *pid; // process's identification
		    int arrival_time;
		    int remaining_burst_time;
	} Process;
	// * Number of processes

	#define NUM_PROCESSES 3
	int main()
	{
		    Process processes[NUM_PROCESSES] =  {
		        {"P1", 0, 5}, {"P2", 3, 3}, {"P3", 6, 4}
		    };

		    //* To keep track of the global CPU time
		    int current_time = 0;
		    for(int i = 0; i < NUM_PROCESSES; i++)
		    {
		        //* If the process hasn't arrived yet, CPU waits (idles)
		        if (current_time < processes[i].arrival_time)
		        {
			            printf("[Time %d] CPU is idle.\n", current_time);
			            current_time = processes[i].arrival_time;
		        }
		        
		        //* Run the process until it finishes
		        while (processes[i].remaining_burst_time > 0)
		        {
		            printf("[Time %d] %s is running (Remaining: %d)\n", current_time, processes[i].pid, processes[i].remaining_burst_time);
		            processes[i].remaining_burst_time--;
		            current_time++;
		        }
		        printf("[Time %d] %s finished execution.\n", current_time, processes[i].pid);
	    }
	    
	    return 0;
	}
```

This demonstrates the rough idea, very easily. However, this particular implementation is a bit naive as it is governed by the order of jobs placed in the array. For example, if we had {"P1", 0, 5}, {"P2", 8, 3}, {"P3", 6, 4}, then upon completion of P1 at 5, it would just be shot to 8, and would defeat FCFS purpose, so a solution could be to sort the array based on arrival time. And that's how you'd end up with an FCFS implementation. However this was just a demonstrative code, so we'll anyway be making changes in it in forth coming steps.


### Step-2: Make it modular
Making it modular, could be our best next step, as that would set us up for adding SJF later on.

Divide the in modules. 
Very basic technique is CTRL+X the logic of fcfs, make a function named fcfs_schedule(), pass the required parameters, and CRLV+V in it.

Taking it one step ahead, which is the best way, is to divide them not in just clean functions but to divide them in different files.
A standard technique to follow is, create separate files of schedules, and their header files
	`|-> main.c`
	`|-> process.h`
	`|-> fcfs.h`
	`|-> fcfs.c`

where process.h is the header file, that giving the structure to the processes, and so must be included in all files.

and we keep a .h file for all the scheduler, so that the main.c could use their functions.

### Step-3: Adding SJF
Add the SJF files - `sjf.c` and `sjf.h`
and work accordingly in `main.c`

Coding SJF: below


### Step-4: Adding Command-line parsing

###### FIRST OF ALL, how is parsing basically done?
Adding the basic command-line argument parsing:
	Update your `main()` function signature like this:
		`int main(int argc, char *argv[])`
	This gives:
	- `argc`: the number of command-line arguments
	- `argv`: the array of strings (C-strings) passed to the program
	
	If we run:
	./scheduler FIFO
	Then:
	- argc == 2
	- argv[0] = "./scheduler"
	- argv[1] = "FIFO"

Now, 
###### How did I implement it?

**Problem:** Had hardcoded algorithm choice in main(). Needed to let users specify `--algorithm FIFO` or `--algorithm SJF` , or any, from command line.

**Implementation Steps:**

1. **Added string comparison** - Included `<string.h>` for `strcmp()` function to compare algorithm names.
2. **Modified main() signature** - Changed from `int main()` to `int main(int argc, char *argv[])` to access command-line arguments.
3. **Simple argument loop** - Iterated through `argv[]` array looking for `--algorithm` flag, then grabbed the next argument as the algorithm name.
4. **Default fallback** - Set `algorithm = "FIFO"` as default so program works even without arguments.
5. **Algorithm dispatch** - Used `if-else` chain with `strcmp()` to call appropriate scheduler function based on user choice.
6. **Basic error handling** - Added check for unknown algorithm names with error message and early return.

**Key Code Pattern:**

c

```c
for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--algorithm") == 0) {
        algorithm = argv[++i];  // Grab next argument
    }
}
```
###### **Result:** Users can now run `./scheduler --algorithm SJF` to choose scheduling algorithm dynamically.
<hr>
<hr>
#### Building SJF
**Problem:** FCFS runs processes in arrival order. SJF needs to pick the shortest job among all arrived processes at each decision point.

**Key Changes Made:**

1. **Added completion tracking** - Added `completed_flag` to Process struct since SJF needs to track which jobs are done.
2. **New decision logic** - Instead of iterating through processes in order, created `find_shortest_arrived_process()` that scans all processes and picks the one with minimum burst time that has arrived and isn't completed.
3. **Idle time handling** - When no processes have arrived yet, added `find_nearest_arriving_process()` to jump CPU time to next arrival instead of tick-by-tick waiting.
4. **Fixed the core bug** - Initially forgot to check `arrival_time <= current_time`, causing scheduler to pick processes that hadn't arrived yet.
5. **Critical fix** - Added `continue` statement after idle handling to prevent trying to run `processes[-1]` when no process is available.

**Result:** Same tick-by-tick simulation framework, but now makes optimal shortest-job-first decisions instead of first-come-first-served decisions.

**Key insight:** SJF is still non-preemptive - once a job starts, it runs to completion. The "shortest job" decision only happens when CPU becomes idle.
