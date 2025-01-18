#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "frames.h"

// Helper function to initialize frames list with numbers 0 to n-1
static List* init_frames(int n) {
    List* frames = (List*)malloc(sizeof(List));
    list_init(frames, free);
    
    // Add frame numbers in reverse order (so we'll get them back in order)
    for (int i = n-1; i >= 0; i--) {
        int* data = (int*)malloc(sizeof(int));
        *data = i;
        if (list_ins_next(frames, NULL, data) != 0) {
            fprintf(stderr, "Failed to initialize frame %d\n", i);
            return NULL;
        }
    }
    return frames;
}

// Helper function to print frames list content
static void print_frames(List* frames) {
    ListElmt* element;
    printf("Available frames: ");
    for (element = list_head(frames); element != NULL; element = list_next(element)) {
        printf("%d ", *(int*)list_data(element));
    }
    printf("\n");
}

int main() {
    // Test 1: Initialize frames
    printf("Test 1: Initializing frames...\n");
    List* frames = init_frames(5);
    assert(frames != NULL);
    assert(list_size(frames) == 5);
    print_frames(frames);

    // Test 2: Allocate frames
    printf("\nTest 2: Allocating frames...\n");
    int frame1 = alloc_frame(frames);
    int frame2 = alloc_frame(frames);
    int frame3 = alloc_frame(frames);
    
    assert(frame1 == 0);
    assert(frame2 == 1);
    assert(frame3 == 2);
    assert(list_size(frames) == 2);
    print_frames(frames);

    // Test 3: Free frames
    printf("\nTest 3: Freeing frames...\n");
    assert(free_frame(frames, frame2) == 0);
    assert(list_size(frames) == 3);
    print_frames(frames);

    // Test 4: Allocate freed frame
    printf("\nTest 4: Allocating freed frame...\n");
    int frame4 = alloc_frame(frames);
    assert(frame4 == 1); // Should get the recently freed frame
    assert(list_size(frames) == 2);
    print_frames(frames);

    // Test 5: Error conditions
    printf("\nTest 5: Testing error conditions...\n");
    // Empty the frames list
    while (list_size(frames) > 0) {
        alloc_frame(frames);
    }
    // Try to allocate from empty list
    assert(alloc_frame(frames) == -1);
    
    // Test 6: Free all frames
    printf("\nTest 6: Freeing all frames...\n");
    assert(free_frame(frames, frame1) == 0);
    assert(free_frame(frames, frame2) == 0);
    assert(free_frame(frames, frame3) == 0);
    assert(free_frame(frames, frame4) == 0);
    assert(list_size(frames) == 4);
    print_frames(frames);

    // Cleanup
    list_destroy(frames);
    free(frames);
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}
