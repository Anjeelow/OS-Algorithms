#include <stdio.h>

// Structure to represent a process
typedef struct {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
} Process;

// Function to calculate completion, turnaround, and waiting times
void calculateTimes(Process processes[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Completion time
        processes[i].completionTime = currentTime + processes[i].burstTime;

        // Turnaround time
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

        // Waiting time
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        // Update current time
        currentTime = processes[i].completionTime;
    }
}

// Function to calculate and display average times
void calculateAndDisplayAverages(Process processes[], int n) {
    float totalTurnAroundTime = 0;
    float totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

// Function to display Gantt chart
void displayGanttChart(Process processes[], int n) {
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf("-");
        }
        printf(" ");
    }
    printf("\n|");

    // Process IDs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime / 2; j++) {
            printf(" ");
        }
        printf("P%d", processes[i].processID);
        for (int j = 0; j < (processes[i].burstTime + 1) / 2; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");

    // Bottom bar
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf("-");
        }
        printf(" ");
    }
    printf("\n");

    // Time labels
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf(" ");
        }
        printf("%d", processes[i].completionTime);
    }
    printf("\n");
}

// Function to display process details
void displayProcesses(Process processes[], int n) {
    printf("\nProcess Details:\n");
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].processID,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    // Calculate times
    calculateTimes(processes, n);

    // Display process details
    displayProcesses(processes, n);

    // Calculate and display averages
    calculateAndDisplayAverages(processes, n);

    // Display Gantt chart
    displayGanttChart(processes, n);

    return 0;
}