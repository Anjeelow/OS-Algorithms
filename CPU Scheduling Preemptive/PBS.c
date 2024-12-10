#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char process_id[5];
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
} Process;

void calculate_times(Process processes[], int n) {
    int completed = 0, current_time = 0;

    while (completed != n) {
        int highest_priority_index = -1;
        int highest_priority = -1;

        // Find process with the highest priority among ready processes
        for (int i = 0; i < n; i++) {
            if (!processes[i].is_completed && processes[i].arrival_time <= current_time) {
                if (processes[i].priority > highest_priority ||
                    (processes[i].priority == highest_priority && processes[i].arrival_time < processes[highest_priority_index].arrival_time)) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) {
            // No process is ready; increment time
            current_time++;
        } else {
            // Process execution
            current_time += processes[highest_priority_index].burst_time;
            processes[highest_priority_index].completion_time = current_time;
            processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
            processes[highest_priority_index].is_completed = true;
            completed++;
        }
    }
}

void display_table(Process processes[], int n) {
    printf("\n+------------+--------------+------------+-----------+----------------+-----------------+-------------+\n");
    printf("| Process ID | Arrival Time | Burst Time | Priority | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("+------------+--------------+------------+-----------+----------------+-----------------+-------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-10s | %-12d | %-10d | %-9d | %-14d | %-15d | %-11d |\n",
               processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].priority, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("+------------+--------------+------------+-----------+----------------+-----------------+-------------+\n");
}

void display_gantt_chart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        if (processes[i].is_completed) {
            printf("----------");
        }
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        if (processes[i].is_completed) {
            printf("   %-6s|", processes[i].process_id);
        }
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        if (processes[i].is_completed) {
            printf("----------");
        }
    }
    printf("\n0");
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].is_completed) {
            time = processes[i].completion_time;
            printf("         %d", time);
        }
    }
    printf("\n");
}

void calculate_averages(Process processes[], int n, float *avg_tat, float *avg_wt) {
    int total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }
    *avg_tat = (float)total_tat / n;
    *avg_wt = (float)total_wt / n;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter the process ID (e.g., 'A', 'B'): ");
        scanf("%s", processes[i].process_id);
        printf("Enter arrival time of %s: ", processes[i].process_id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time of %s: ", processes[i].process_id);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority of %s (higher number means higher priority): ", processes[i].process_id);
        scanf("%d", &processes[i].priority);
        processes[i].is_completed = false; // Initialize completion status
    }

    calculate_times(processes, n);

    display_table(processes, n);

    float avg_tat, avg_wt;
    calculate_averages(processes, n, &avg_tat, &avg_wt);
    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    display_gantt_chart(processes, n);

    return 0;
}