#include <stdio.h>
#include <stdlib.h>

// Structure to represent the disk arm and its movement
typedef struct {
    int initialPosition;
    int *requests;
    int requestCount;
} DiskArm;

// Function to calculate total head movement and process requests
void processRequests(DiskArm *diskArm) {
    int totalHeadMovement = 0;
    int currentPosition = diskArm->initialPosition;

    printf("\nProcessing Order: \n");

    for (int i = 0; i < diskArm->requestCount; i++) {
        printf("Track %d\n", diskArm->requests[i]);

        // Calculate head movement
        totalHeadMovement += abs(currentPosition - diskArm->requests[i]);
        currentPosition = diskArm->requests[i];
    }

    printf("\nTotal Head Movement: %d\n", totalHeadMovement);
}

int main() {
    DiskArm diskArm;

    // Input initial position of the disk arm
    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &diskArm.initialPosition);

    // Input number of track requests
    printf("Enter the number of track requests: ");
    scanf("%d", &diskArm.requestCount);

    diskArm.requests = (int *)malloc(diskArm.requestCount * sizeof(int));

    // Input track requests
    printf("Enter the track requests: \n");
    for (int i = 0; i < diskArm.requestCount; i++) {
        scanf("%d", &diskArm.requests[i]);
    }

    // Process the requests
    processRequests(&diskArm);

    // Free allocated memory
    free(diskArm.requests);

    return 0;
}