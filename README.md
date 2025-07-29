# CPU_Scheduler

# 🧠 Scheduler Simulator — A Time-Driven OS Lab in Code

A simple but insightful **CPU Scheduler Simulator** built in C that mimics how an Operating System manages CPU time among multiple processes. It supports multiple scheduling algorithms like **FCFS (First-Come-First-Serve)** and **SJF (Shortest Job First)** in a **tick-by-tick simulation model**.

> This isn't a full OS kernel. It's a **learning-driven simulation** where each tick represents a CPU time unit, and every state transition is logged for clarity.

---

## 🚀 Features

- ✅ Tick-by-tick simulation (1 tick = 1 CPU time unit)
- ✅ Multiple Scheduling Algorithms: FCFS, SJF (non-preemptive)
- ✅ Modular code structure (clean separation of scheduling logic)
- ✅ Command-line algorithm selection
- ✅ Handles CPU idle time and I/O-aware jobs (future-ready)
- ✅ Metrics tracking: Turnaround Time, Waiting Time, Response Time (WIP)
- ✅ Designed for easy extension to RR, SRTF, MLFQ, etc.

---

## 🧩 Simulation Model

At each tick:
- Tracks which process is **running**
- Which are **waiting** in the ready queue
- Which are **doing I/O** (extension planned)
- How they **move between states**

It’s like a time-driven OS lab session – but in C code.

---

## 📄 Input Format

Each process has:
- `pid`: Process ID (string)
- `arrival_time`: When it arrives in the system
- `CPU burst(s)`: A sequence of CPU time requirements (e.g., `4,5,6`)
- `I/O burst(s)`: (Optional) Time spent doing I/O in between CPU bursts (e.g., `2,3`)

**Note:** Initial version only supports single burst (no I/O interleaving yet).

<hr>

Command:
```bash
./scheduler --algorithm SJF
```
<hr>

How to Run
Build
```bash
gcc main.c fcfs.c sjf.c -o scheduler
```
Run
```bash
./scheduler --algorithm FCFS
```
or
```bash
./scheduler --algorithm SJF
```
