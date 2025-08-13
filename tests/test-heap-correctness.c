#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heap.h"


int main() {

    // Initialization of the needed variables
    struct heap *heap = malloc(sizeof(struct heap));
    heap->nb_nodes = 0;
    heap->root = NULL;

    // Test of the insert function with the costs 1 to 50
    for (int i = 1; i < 51; i++){
        insert(i, heap);
    }

    // Check by printing the heap
    print_heap(heap);

    // Test of the extract min function
    for (int i = 1; i < 51; i++){
        int k = extract_min(heap);

        // Check by printing the heap and the int value from extract_min
        print_heap(heap);
        printf("%d\n", k);
    }

    // Important to free the allocated memories
    free(heap->root);
    free(heap);
    
    return 0;
}