#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function Prototypes
void priority_non_preemptive_scheduling(struct Process processes[], int n, int execution_order[]);
void calculate_average_times(struct Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time);
void display_results(struct Process processes[], int n, float avg_turnaround_time, float avg_waiting_time);
void display_gantt_chart(struct Process processes[], int n, int execution_order[]);

int main() {
    struct Process processes[] = {
        {1, 3, 4, 2},
        {2, 5, 9, 1},
        {3, 8, 4, 2},
        {4, 0, 7, 1},
        {5, 12, 6, 1}
    };
    
    int n = sizeof(processes) / sizeof(processes[0]);
    float avg_turnaround_time, avg_waiting_time;
    int execution_order[n];
    
    priority_non_preemptive_scheduling(processes, n, execution_order);
    calculate_average_times(processes, n, &avg_turnaround_time, &avg_waiting_time);
    display_results(processes, n, avg_turnaround_time, avg_waiting_time);
    display_gantt_chart(processes, n, execution_order);
    
    return 0;
}

void priority_non_preemptive_scheduling(struct Process processes[], int n, int execution_order[]) {
    int completed = 0, current_time = 0, idx = -1;
    
    // Track completed processes and choose process with highest priority
    while (completed < n) {
        int highest_priority = 9999;
        idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            
            current_time = processes[idx].completion_time;
            
            // Store the order of execution
            execution_order[completed] = idx;
            completed++;
        } else {
            current_time++;
        }
    }
}

void calculate_average_times(struct Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    int total_turnaround_time = 0, total_waiting_time = 0;
    
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }
    
    *avg_turnaround_time = (float)total_turnaround_time / n;
    *avg_waiting_time = (float)total_waiting_time / n;
}

void display_results(struct Process processes[], int n, float avg_turnaround_time, float avg_waiting_time) {
    printf("Process\t\tArrival Time\tBurst Time\tPriority\tCompletion Time\t\tTurnaround Time\t\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%-15d%-16d%-16d%-16d%-24d%-24d%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].priority,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

void display_gantt_chart(struct Process processes[], int n, int execution_order[]) {
    printf("\nGantt Chart:\n");
    
    // Print top border
    for (int x = 1; x <= n; x++) {
        printf("        ");
        for (int i = 0; i < x; i++) {
            printf(" ");
            int burst_time = processes[execution_order[i]].burst_time;
            for (int j = 0; j < burst_time; j++) {
                printf("--");
            }
        }
        printf("\n%c.)", x + 96);
        printf("     |");

        // Print process IDs in execution order
        for (int i = 0; i < x; i++) {
            int burst_time = processes[execution_order[i]].burst_time;
            for (int j = 0; j < burst_time - 1; j++) {
                printf(" ");
            }
            printf("P%d", processes[execution_order[i]].pid);
            for (int j = 0; j < burst_time - 1; j++) {
                printf(" ");
            }
            printf("|");
        }
        printf("\n");

        // Print bottom border
        printf("        ");
        for (int i = 0; i < x; i++) {
            printf(" ");
            int burst_time = processes[execution_order[i]].burst_time;
            for (int j = 0; j < burst_time; j++) {
                printf("--");
            }
        }
        printf("\n");

        // Print time markers
        printf("        ");
        int current_time = 0;
        printf("0");
        for (int i = 0; i < x; i++) {
            int burst_time = processes[execution_order[i]].burst_time;
            current_time += processes[execution_order[i]].burst_time;
            for (int j = 0; j < burst_time * 2 - 1; j++) {
                printf(" ");
            }
            if (current_time < 10) {
                printf(" ");
            }
            printf("%d", current_time);
        }
        printf("\n\n");
    }
}
