#include <stdio.h>
#include <limits.h>

struct Process {
    int id;            
    int arrival_time;  
    int burst_time;    
    int completion_time;  
    int turnaround_time;  
    int waiting_time;     
};

void sjf_non_preemptive(struct Process proc[], int n) {
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int completed = 0;
    int current_time = 0;

    int is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed < n) {
        int min_burst_time = INT_MAX;
        int shortest_job_index = -1;

        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && proc[i].arrival_time <= current_time &&
                proc[i].burst_time < min_burst_time) {
                min_burst_time = proc[i].burst_time;
                shortest_job_index = i;
            }
        }

        if (shortest_job_index == -1) {
            // If no process has arrived yet, move time forward to the next available process
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!is_completed[i] && proc[i].arrival_time < next_arrival_time) {
                    next_arrival_time = proc[i].arrival_time;
                }
            }
            current_time = next_arrival_time;
            continue;
        }

        // Update current time and process metrics for the selected job
        current_time += proc[shortest_job_index].burst_time;
        proc[shortest_job_index].completion_time = current_time;
        proc[shortest_job_index].turnaround_time =
            proc[shortest_job_index].completion_time - proc[shortest_job_index].arrival_time;
        proc[shortest_job_index].waiting_time =
            proc[shortest_job_index].turnaround_time - proc[shortest_job_index].burst_time;

        total_turnaround_time += proc[shortest_job_index].turnaround_time;
        total_waiting_time += proc[shortest_job_index].waiting_time;

        is_completed[shortest_job_index] = 1;
        completed++;
    }

    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

void display_gantt_chart(struct Process proc[], int n) {
    const int scale = 2;  
    int current_time = 0;

    printf("\nGantt Chart:\n");
    
    for (int x = 1; x <= n; x++) {

        printf("%c.)      ", 'a' + x - 1);

        for (int i = 0; i < x; i++) {
            printf(" ");
            for (int j = 0; j < proc[i].burst_time * scale; j++) {
                printf("-");
            }
        }
        printf("\n         ");

        for (int i = 0; i < x; i++) {
            printf("| P%d ", proc[i].id);
            for (int j = 0; j < proc[i].burst_time * scale - 4; j++) {
                printf(" ");
            }
        }
        printf("|\n         ");

        for (int i = 0; i < x; i++) {
            printf(" ");
            for (int j = 0; j < proc[i].burst_time * scale; j++) {
                printf("-");
            }
        }
        printf("\n");

        current_time = 0;
        printf("          %d", current_time);
        for (int i = 0; i < x; i++) {
            current_time += proc[i].burst_time;
            int marker_spacing = proc[i].burst_time * scale - 1;
            for (int j = 0; j < marker_spacing; j++) {
                printf(" ");
            }
            printf("%d", current_time);
        }
        printf("\n\n");
    }
}

int main() {
    struct Process processes[] = {
        {1, 0, 8},
        {2, 3, 4},
        {3, 4, 5},
        {4, 6, 3},
        {5, 10, 2}
    };

    int n = sizeof(processes) / sizeof(processes[0]);
    
    sjf_non_preemptive(processes, n);
    display_gantt_chart(processes, n);

    return 0;
}