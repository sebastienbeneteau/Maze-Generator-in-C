#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heap.h"
#include "time.h"


int main() {

    // Opening of the file
    FILE *p_file = NULL;

    p_file = fopen("data_complexity_heap.csv", "w");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file data_complexity_heap.csv!\n");
        exit(EXIT_FAILURE);
    }

    // Loop with doubling the experience each time
    for (int n = 20; n < 10000000; n *= 2) {

        // Initialization
        struct heap *heap = malloc(sizeof(struct heap));
        heap->nb_nodes = 0;
        heap->root = NULL;

        // Just to make sure I use the k variable
        int k = 0;
        k += 1;

        // INSERT TEST ----------------------------------------------------------------------------
        // Start clock for insert
        clock_t start_insert = clock();

        // Insert loop
        for (int i = 1; i < n; i++){
            insert(i, heap);
        }

        // Stop the time
        clock_t end_insert = clock();

        // Storage of the time_to_insert
        double time_to_insert = (double) (end_insert - start_insert) / CLOCKS_PER_SEC;

        // EXTRACT TEST ----------------------------------------------------------------------------
        // Start clock for extract
        clock_t start_extract = clock();
        
        // Extract loop
        for (int i = 1; i < n; i++){
            k = extract_min(heap);
        }

        // Stop the time
        clock_t end_extract = clock();

        // Storage of the time_to_extract
        double time_to_extract = (double) (end_extract - start_extract) / CLOCKS_PER_SEC;

        fprintf(p_file, "%d,%lf,%lf\n", n, time_to_insert, time_to_extract);

        // Free the allocated memory
        free(heap->root);
        free(heap);
    }

    // Closing of the file
    fclose(p_file);
    p_file = NULL;

    return 0;
}