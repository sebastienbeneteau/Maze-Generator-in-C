#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "map.h"

#define INFINI 2147483647 //Represents the infinity with the maximum number for 32 bits integers


int main(int argc, char *argv[]){
    // testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name!\n");
        exit(EXIT_FAILURE);
    }

    // Initialization of the test map
    struct map map_test = load(argv[1]);

    // Declaration of the neighbors to compare
    struct neighbors neighbor_a_comparer = {2, { 10, 1, -1, -1 }, { 0, -14, INFINI, INFINI}};
    int node_a_comparer = 0;

    // Use of find_neighbors function in order to found the neighbors of map_test
    struct neighbors neighbors_map_test = find_neighbors(map_test, node_a_comparer);
    
    // Beginning of the comparison
    assert(neighbor_a_comparer.nb == neighbors_map_test.nb);
    for (int i=0; i < 4; i++){
        assert(neighbor_a_comparer.array_neighbors[i] == neighbors_map_test.array_neighbors[i]);
        assert(neighbor_a_comparer.array_cost[i] == neighbors_map_test.array_cost[i]);
    }

    // Important free the heap
    free(map_test.array_edges);

    return 0;
}
