#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement and process requests
void clookDiskScheduling(int initial_position, int *requests, int n, int disk_size) {
    int i, total_head_movement = 0, current_position = initial_position;
    int *sorted_requests = (int *)malloc(n * sizeof(int));
    
    // Copy and sort requests
    for (i = 0; i < n; i++) {
        sorted_requests[i] = requests[i];
    }
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Find the start point in the sorted list
    int start_index = 0;
    while (start_index < n && sorted_requests[start_index] < initial_position) {
        start_index++;
    }

    printf("\nOrder of servicing tracks:\n");

    // Process requests in the direction of increasing track numbers
    for (i = start_index; i < n; i++) {
        printf("%d ", sorted_requests[i]);
        total_head_movement += abs(current_position - sorted_requests[i]);
        current_position = sorted_requests[i];
    }

    // Jump to the lowest track request
    if (start_index > 0) {
        total_head_movement += abs(current_position - sorted_requests[0]);
        current_position = sorted_requests[0];
        printf("%d ", current_position);
    }

    // Process the remaining requests
    for (i = 1; i < start_index; i++) {
        printf("%d ", sorted_requests[i]);
        total_head_movement += abs(current_position - sorted_requests[i]);
        current_position = sorted_requests[i];
    }

    printf("\n\nTotal head movement: %d\n", total_head_movement);

    free(sorted_requests);
}

int main() {
    int initial_position, n, disk_size;

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initial_position);

    printf("Enter the disk size (maximum track number): ");
    scanf("%d", &disk_size);

    printf("Enter the number of track requests: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));

    printf("Enter the track requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    clookDiskScheduling(initial_position, requests, n, disk_size);

    free(requests);
    return 0;
}