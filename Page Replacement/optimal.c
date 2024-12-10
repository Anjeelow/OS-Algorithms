#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a page and its metadata
typedef struct {
    int pageNumber;
    int frequency; // For LFU
    int lastUsed;  // For LRU
} Page;

// Function prototypes
void simulateFIFO(int pages[], int pageCount, int frameCount);
void simulateLRU(int pages[], int pageCount, int frameCount);
void simulateLFU(int pages[], int pageCount, int frameCount);
void simulateOptimal(int pages[], int pageCount, int frameCount);

// Function to find page in memory (-1 if not found)
int findPage(Page frames[], int frameCount, int pageNumber) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i].pageNumber == pageNumber) {
            return i;
        }
    }
    return -1;
}

// FIFO simulation
void simulateFIFO(int pages[], int pageCount, int frameCount) {
    printf("\nSimulating FIFO:\n");
    Page frames[frameCount];
    int front = 0, pageFaults = 0, pageHits = 0;

    memset(frames, -1, sizeof(frames));

    for (int i = 0; i < pageCount; i++) {
        if (findPage(frames, frameCount, pages[i]) == -1) {
            frames[front] = (Page){pages[i], 0, 0};
            front = (front + 1) % frameCount;
            pageFaults++;
            printf("Page fault: Adding %d\n", pages[i]);
        } else {
            pageHits++;
            printf("Page hit: %d\n", pages[i]);
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

// LRU simulation
void simulateLRU(int pages[], int pageCount, int frameCount) {
    printf("\nSimulating LRU:\n");
    Page frames[frameCount];
    int pageFaults = 0, pageHits = 0, time = 0;

    memset(frames, -1, sizeof(frames));

    for (int i = 0; i < pageCount; i++) {
        time++;
        int index = findPage(frames, frameCount, pages[i]);

        if (index == -1) {
            int lruIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (frames[j].pageNumber == -1 || frames[j].lastUsed < frames[lruIndex].lastUsed) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = (Page){pages[i], 0, time};
            pageFaults++;
            printf("Page fault: Adding %d\n", pages[i]);
        } else {
            frames[index].lastUsed = time;
            pageHits++;
            printf("Page hit: %d\n", pages[i]);
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

// LFU simulation
void simulateLFU(int pages[], int pageCount, int frameCount) {
    printf("\nSimulating LFU:\n");
    Page frames[frameCount];
    int pageFaults = 0, pageHits = 0;

    memset(frames, -1, sizeof(frames));

    for (int i = 0; i < pageCount; i++) {
        int index = findPage(frames, frameCount, pages[i]);

        if (index == -1) {
            int lfuIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (frames[j].pageNumber == -1 || frames[j].frequency < frames[lfuIndex].frequency) {
                    lfuIndex = j;
                }
            }
            frames[lfuIndex] = (Page){pages[i], 1, 0};
            pageFaults++;
            printf("Page fault: Adding %d\n", pages[i]);
        } else {
            frames[index].frequency++;
            pageHits++;
            printf("Page hit: %d\n", pages[i]);
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

// Optimal simulation
void simulateOptimal(int pages[], int pageCount, int frameCount) {
    printf("\nSimulating Optimal:\n");
    Page frames[frameCount];
    int pageFaults = 0, pageHits = 0;

    memset(frames, -1, sizeof(frames));

    for (int i = 0; i < pageCount; i++) {
        int index = findPage(frames, frameCount, pages[i]);

        if (index == -1) {
            int optIndex = 0, farthest = i;
            for (int j = 0; j < frameCount; j++) {
                int nextUse = pageCount;
                for (int k = i + 1; k < pageCount; k++) {
                    if (frames[j].pageNumber == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse > farthest) {
                    farthest = nextUse;
                    optIndex = j;
                }
            }
            frames[optIndex] = (Page){pages[i], 0, 0};
            pageFaults++;
            printf("Page fault: Adding %d\n", pages[i]);
        } else {
            pageHits++;
            printf("Page hit: %d\n", pages[i]);
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

int main() {
    int pageCount, frameCount;

    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);

    int pages[pageCount];
    printf("Enter the sequence of pages: \n");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    simulateFIFO(pages, pageCount, frameCount);
    simulateLRU(pages, pageCount, frameCount);
    simulateLFU(pages, pageCount, frameCount);
    simulateOptimal(pages, pageCount, frameCount);

    return 0;
}
