#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_REQUESTS 100
#define DISK_SIZE 200

typedef struct {
    int requests[MAX_REQUESTS];
    int num_requests;
    int initial_position;
    int total_head_movement;
    int served_requests[MAX_REQUESTS];
    int num_served_requests;
} DiskScheduler;

void initialize_scheduler(DiskScheduler *scheduler, int initial_pos);
void add_request(DiskScheduler *scheduler, int track);
void c_scan_algorithm(DiskScheduler *scheduler);
void display_results(DiskScheduler *scheduler);
void sort_requests(int arr[], int n);

int main() {
    DiskScheduler scheduler;
    
    int initial_position = 50;
    int track_requests[] = {82, 170, 43, 140, 24, 16, 190};
    int num_requests = sizeof(track_requests) / sizeof(track_requests[0]);

    initialize_scheduler(&scheduler, initial_position);

    for (int i = 0; i < num_requests; i++) {
        add_request(&scheduler, track_requests[i]);
    }

    c_scan_algorithm(&scheduler);

    display_results(&scheduler);

    return 0;
}

void initialize_scheduler(DiskScheduler *scheduler, int initial_pos) {
    scheduler->initial_position = initial_pos;
    scheduler->num_requests = 0;
    scheduler->total_head_movement = 0;
    scheduler->num_served_requests = 0;
}

void add_request(DiskScheduler *scheduler, int track) {
    if (scheduler->num_requests < MAX_REQUESTS) {
        scheduler->requests[scheduler->num_requests++] = track;
    } else {
        printf("Maximum request limit reached!\n");
    }
}

void sort_requests(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void c_scan_algorithm(DiskScheduler *scheduler) {
    if (scheduler->num_requests == 0) return;

    sort_requests(scheduler->requests, scheduler->num_requests);

    int current_pos = scheduler->initial_position;
    int total_movement = 0;

    int start_index = 0;
    while (start_index < scheduler->num_requests && 
           scheduler->requests[start_index] < current_pos) {
        start_index++;
    }

    for (int i = start_index; i < scheduler->num_requests; i++) {
        total_movement += abs(current_pos - scheduler->requests[i]);
        current_pos = scheduler->requests[i];
        scheduler->served_requests[scheduler->num_served_requests++] = current_pos;
    }

    if (current_pos != DISK_SIZE - 1) {
        total_movement += (DISK_SIZE - 1 - current_pos);
        current_pos = DISK_SIZE - 1;
    }

    total_movement += current_pos;
    current_pos = 0;

    for (int i = 0; i < start_index; i++) {
        total_movement += abs(current_pos - scheduler->requests[i]);
        current_pos = scheduler->requests[i];
        scheduler->served_requests[scheduler->num_served_requests++] = current_pos;
    }

    scheduler->total_head_movement = total_movement;
}

void display_results(DiskScheduler *scheduler) {
    printf("\nC-SCAN Disk Scheduling Results\n");
    printf("------------------------------\n");
    
    printf("Initial Disk Arm Position: %d\n", scheduler->initial_position);
    
    printf("\nTrack Requests: ");
    for (int i = 0; i < scheduler->num_requests; i++) {
        printf("%d ", scheduler->requests[i]);
    }
    printf("\n\n");

    printf("Served Track Order: ");
    for (int i = 0; i < scheduler->num_served_requests; i++) {
        printf("%d ", scheduler->served_requests[i]);
    }
    printf("\n\n");

    printf("Total Head Movement: %d\n", scheduler->total_head_movement);
    printf("Average Head Movement: %.2f\n", 
           (float)scheduler->total_head_movement / scheduler->num_requests);
}