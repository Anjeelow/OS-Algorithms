#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function to check if a page is present in the frames
bool isPageInFrames(int frames[], int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// FIFO Page Replacement Algorithm
void fifoPageReplacement(int pages[], int num_pages, int num_frames) {
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int page_hits = 0;      // Counter for page hits
    int current_frame = 0;

    // Initialize frames to -1 (indicating empty slots)
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        printf("%d\t", pages[i]);

        // Check if page is already in one of the frames
        if (!isPageInFrames(frames, num_frames, pages[i])) {
            frames[current_frame] = pages[i];
            current_frame = (current_frame + 1) % num_frames;
            page_faults++;

            // Print the frames
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] != -1) {
                    printf("%d ", frames[j]);
                } else {
                    printf("- ");
                }
            }
        } else {
            page_hits++;  // Increment page hits
            printf("Page hit");
        }
        printf("\n");
    }

    // Output statistics
    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", page_hits);
    printf("Page Hit Percentage: %.2f%%\n", (page_hits / (float)num_pages) * 100);
    printf("Page Fault Percentage: %.2f%%\n", (page_faults / (float)num_pages) * 100);
}

int main() {
    int pages[MAX_PAGES];
    int num_pages, num_frames;

    // Input number of frames
    printf("Enter the number of frames (max %d): ", MAX_FRAMES);
    scanf("%d", &num_frames);

    if (num_frames <= 0 || num_frames > MAX_FRAMES) {
        printf("Invalid number of frames! Please enter a value between 1 and %d.\n", MAX_FRAMES);
        return 1;
    }

    // Input number of pages
    printf("Enter the number of pages (max %d): ", MAX_PAGES);
    scanf("%d", &num_pages);

    if (num_pages <= 0 || num_pages > MAX_PAGES) {
        printf("Invalid number of pages! Please enter a value between 1 and %d.\n", MAX_PAGES);
        return 1;
    }

    // Input the pages
    printf("Enter the page reference string: ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\nPage Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\nNumber of Frames: %d\n", num_frames);

    fifoPageReplacement(pages, num_pages, num_frames);

    return 0;
}
