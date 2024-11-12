from queue import PriorityQueue

class Process:
    def __init__(self, pid, arrival, burst, priority):
        self.pid = pid
        self.arrival = arrival
        self.burst = burst
        self.priority = priority
        self.remaining_time = burst
        self.start_time = None
        self.finish_time = None

def calculate_times(schedule, processes):
    n = len(processes)
    waiting_time, turnaround_time = 0, 0
    for pid, finish_time in schedule:
        process = next(p for p in processes if p.pid == pid)
        process.finish_time = finish_time
        turnaround_time += finish_time - process.arrival
        waiting_time += finish_time - process.arrival - process.burst
    avg_waiting = waiting_time / n
    avg_turnaround = turnaround_time / n
    return avg_waiting, avg_turnaround

def fcfs(processes):
    processes.sort(key=lambda x: x.arrival)
    time, schedule = 0, []
    for p in processes:
        time = max(time, p.arrival) + p.burst
        schedule.append((p.pid, time))
    return schedule

def sjf_preemptive(processes):
    processes.sort(key=lambda x: x.arrival)
    pq, schedule = PriorityQueue(), []
    time, i = 0, 0
    while i < len(processes) or not pq.empty():
        while i < len(processes) and processes[i].arrival <= time:
            pq.put((processes[i].remaining_time, processes[i]))
            i += 1
        if pq.empty():
            time = processes[i].arrival
        else:
            rem_time, p = pq.get()
            time += 1
            p.remaining_time -= 1
            if p.remaining_time > 0:
                pq.put((p.remaining_time, p))
            if p.remaining_time == 0:
                schedule.append((p.pid, time))
    return schedule

def priority_non_preemptive(processes):
    processes.sort(key=lambda x: (x.arrival, x.priority))
    time, schedule = 0, []
    for p in processes:
        time = max(time, p.arrival) + p.burst
        schedule.append((p.pid, time))
    return schedule

def round_robin(processes, quantum):
    time, queue, schedule = 0, [], []
    remaining = {p.pid: p.burst for p in processes}
    while processes or queue:
        while processes and processes[0].arrival <= time:
            queue.append(processes.pop(0))
        if queue:
            p = queue.pop(0)
            exec_time = min(quantum, remaining[p.pid])
            time += exec_time
            remaining[p.pid] -= exec_time
            if remaining[p.pid] > 0:
                queue.append(p)
            if remaining[p.pid] == 0:
                schedule.append((p.pid, time))
        else:
            time = processes[0].arrival
    return schedule

def get_processes():
    n = int(input("Enter the number of processes: "))
    processes = []
    for i in range(n):
        pid = i + 1
        arrival = int(input(f"Enter arrival time for process {pid}: "))
        burst = int(input(f"Enter burst time for process {pid}: "))
        priority = int(input(f"Enter priority for process {pid} (lower value means higher priority): "))
        processes.append(Process(pid, arrival, burst, priority))
    return processes

if __name__ == "__main__":
    processes = get_processes()

    fcfs_schedule = fcfs(processes[:])
    avg_waiting_fcfs, avg_turnaround_fcfs = calculate_times(fcfs_schedule, processes)
    print("\nFCFS Scheduling:")
    print(f"Schedule: {fcfs_schedule}")
    print(f"Average Waiting Time: {avg_waiting_fcfs:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_fcfs:.2f}")

    sjf_schedule = sjf_preemptive(processes[:])
    avg_waiting_sjf, avg_turnaround_sjf = calculate_times(sjf_schedule, processes)
    print("\nSJF Preemptive Scheduling:")
    print(f"Schedule: {sjf_schedule}")
    print(f"Average Waiting Time: {avg_waiting_sjf:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_sjf:.2f}")

    priority_schedule = priority_non_preemptive(processes[:])
    avg_waiting_priority, avg_turnaround_priority = calculate_times(priority_schedule, processes)
    print("\nPriority Non-Preemptive Scheduling:")
    print(f"Schedule: {priority_schedule}")
    print(f"Average Waiting Time: {avg_waiting_priority:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_priority:.2f}")

    quantum = int(input("\nEnter time quantum for Round Robin: "))
    rr_schedule = round_robin(processes[:], quantum)
    avg_waiting_rr, avg_turnaround_rr = calculate_times(rr_schedule, processes)
    print("\nRound Robin Scheduling:")
    print(f"Schedule: {rr_schedule}")
    print(f"Average Waiting Time: {avg_waiting_rr:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_rr:.2f}")

"""
***************************************************************************************

Input:

Number of processes: 3

Arrival time for process 1: 0

Burst time for process 1: 20

Priority for process 1: 1

Arrival time for process 2: 0

Burst time for process 2: 3

Priority for process 2: 2

Arrival time for process 3: 0

Burst time for process 3: 4

Priority for process 3: 3

"""
