#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

void srtf_scheduling(Process proc[], int n);
void display_gantt_chart(Process gantt_chart[], int chart_length);

int main() {
    Process processes[MAX_PROCESSES] = {
        {1, 0, 8, 8, 0, 0, 0},
        {2, 1, 4, 4, 0, 0, 0},
        {3, 2, 2, 2, 0, 0, 0},
        {4, 3, 1, 1, 0, 0, 0},
        {5, 4, 3, 3, 0, 0, 0},
        {6, 5, 2, 2, 0, 0, 0},
    };

    int n = 6;
    srtf_scheduling(processes, n);

    return 0;
}

void srtf_scheduling(Process proc[], int n) {
    int total_time = 0, completed = 0, shortest, current_time;
    float total_waiting_time = 0, total_turnaround_time = 0;
    
    Process gantt_chart[MAX_PROCESSES * 2];
    int chart_length = 0;

    // Find total time
    for (int i = 0; i < n; i++) {
        total_time += proc[i].burst_time;
        proc[i].remaining_time = proc[i].burst_time;
    }

    // Process until all processes are completed
    current_time = 0;
    while (completed != n) {
        shortest = -1;
        int min_remaining_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && 
                proc[i].remaining_time > 0 && 
                proc[i].remaining_time < min_remaining_time) {
                shortest = i;
                min_remaining_time = proc[i].remaining_time;
            }
        }

        if (shortest != -1) {
            gantt_chart[chart_length] = proc[shortest];
            gantt_chart[chart_length].completion_time = current_time + 1;
            chart_length++;

            proc[shortest].remaining_time--;
            current_time++;

            if (proc[shortest].remaining_time == 0) {
                completed++;
                
                proc[shortest].completion_time = current_time;
                proc[shortest].turnaround_time = proc[shortest].completion_time - proc[shortest].arrival_time;
                proc[shortest].waiting_time = proc[shortest].turnaround_time - proc[shortest].burst_time;

                total_waiting_time += proc[shortest].waiting_time;
                total_turnaround_time += proc[shortest].turnaround_time;
            }
        } else {
            current_time++;
        }
    }

    // Display results
    printf("\nProcess Details:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", 
               proc[i].pid, 
               proc[i].arrival_time, 
               proc[i].burst_time, 
               proc[i].completion_time, 
               proc[i].waiting_time, 
               proc[i].turnaround_time);
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");
    display_gantt_chart(gantt_chart, chart_length);

    printf("\nAverage Waiting Time: %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void display_gantt_chart(Process gantt_chart[], int chart_length) {
    for (int i = 0; i < chart_length; i++) {
        printf("+------");
    }
    printf("+\n");

    for (int i = 0; i < chart_length; i++) {
        printf("|  P%d  ", gantt_chart[i].pid);
    }
    printf("|\n");

    for (int i = 0; i < chart_length; i++) {
        printf("+------");
    }
    printf("+\n");

    printf("0");
    for (int i = 0; i < chart_length; i++) {
        printf("%7d", gantt_chart[i].completion_time);
    }
    printf("\n");
}