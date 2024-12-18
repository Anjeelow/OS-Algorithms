#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FRAMES 10
#define MAX_REFERENCE_STRING 100

typedef struct {
    int page_number;
    int last_used_time;
} Page;

typedef struct {
    Page frames[MAX_FRAMES];
    int num_frames;
    int current_time;
    int total_references;
    int page_hits;
    int page_faults;
} LRUSimulator;

void initialize_simulator(LRUSimulator *sim, int num_frames);
void simulate_page_replacement(LRUSimulator *sim, int *reference_string, int reference_length);
void display_memory_state(LRUSimulator *sim);
void log_page_replacement(int removed_page, int new_page);
void print_performance_metrics(LRUSimulator *sim);

int main() {
    LRUSimulator sim;
    
    int reference_string[MAX_REFERENCE_STRING];
    int reference_length;
    int num_frames;
    
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    if (num_frames <= 0 || num_frames > MAX_FRAMES) {
        printf("Invalid number of frames. Please enter a value between 1 and %d.\n", MAX_FRAMES);
        return 1;
    }

    printf("Enter the length of the reference string: ");
    scanf("%d", &reference_length);

    if (reference_length <= 0 || reference_length > MAX_REFERENCE_STRING) {
        printf("Invalid reference string length. Please enter a value between 1 and %d.\n", MAX_REFERENCE_STRING);
        return 1;
    }

    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < reference_length; i++) {
        scanf("%d", &reference_string[i]);
    }
    
    initialize_simulator(&sim, num_frames);
    
    printf("LRU Page Replacement Algorithm Simulation\n");
    printf("----------------------------------------\n");
    printf("Number of Frames: %d\n", num_frames);
    printf("Reference String Length: %d\n\n", reference_length);
    
    simulate_page_replacement(&sim, reference_string, reference_length);
    
    return 0;
}

void initialize_simulator(LRUSimulator *sim, int num_frames) {
    sim->num_frames = num_frames;
    sim->current_time = 0;
    sim->total_references = 0;
    sim->page_hits = 0;
    sim->page_faults = 0;
    
    for (int i = 0; i < num_frames; i++) {
        sim->frames[i].page_number = -1;
        sim->frames[i].last_used_time = -1;
    }
}

void simulate_page_replacement(LRUSimulator *sim, int *reference_string, int reference_length) {
    for (int i = 0; i < reference_length; i++) {
        int current_page = reference_string[i];
        bool page_found = false;
        int empty_frame = -1;
        
        // Check if page is already in memory
        for (int j = 0; j < sim->num_frames; j++) {
            if (sim->frames[j].page_number == current_page) {
                sim->page_hits++;
                sim->frames[j].last_used_time = sim->current_time;
                page_found = true;
                break;
            }
            
            if (sim->frames[j].page_number == -1 && empty_frame == -1) {
                empty_frame = j;
            }
        }
        
        if (!page_found) {
            sim->page_faults++;
            
            // If empty frame exists, use it
            if (empty_frame != -1) {
                sim->frames[empty_frame].page_number = current_page;
                sim->frames[empty_frame].last_used_time = sim->current_time;
            }
            else {
                // Find least recently used page
                int lru_index = 0;
                for (int j = 1; j < sim->num_frames; j++) {
                    if (sim->frames[j].last_used_time < sim->frames[lru_index].last_used_time) {
                        lru_index = j;
                    }
                }
                
                log_page_replacement(sim->frames[lru_index].page_number, current_page);
                
                sim->frames[lru_index].page_number = current_page;
                sim->frames[lru_index].last_used_time = sim->current_time;
            }
        }
        
        printf("Reference %d: %d\n", i + 1, current_page);
        display_memory_state(sim);
        printf("\n");
        
        sim->current_time++;
        sim->total_references++;
    }
    
    print_performance_metrics(sim);
}

void display_memory_state(LRUSimulator *sim) {
    printf("Memory State: [ ");
    for (int i = 0; i < sim->num_frames; i++) {
        if (sim->frames[i].page_number != -1) {
            printf("%d ", sim->frames[i].page_number);
        } else {
            printf("- ");
        }
    }
    printf("]\n");
}

void log_page_replacement(int removed_page, int new_page) {
    printf("Page Replacement: %d replaced by %d\n", removed_page, new_page);
}

void print_performance_metrics(LRUSimulator *sim) {
    printf("\nPerformance Metrics\n");
    printf("------------------\n");
    printf("Total Page References: %d\n", sim->total_references);
    printf("Page Hits: %d\n", sim->page_hits);
    printf("Page Faults: %d\n", sim->page_faults);
    
    float hit_percentage = ((float)sim->page_hits / sim->total_references) * 100;
    float fault_percentage = ((float)sim->page_faults / sim->total_references) * 100;
    
    printf("Page Hit Percentage: %.2f%%\n", hit_percentage);
    printf("Page Fault Percentage: %.2f%%\n", fault_percentage);
}
