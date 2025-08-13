#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "maze.h"
#include "prim.h"

#define INFINI 2147483647 //Represents the infinity with the maximum number for 32 bits integers


int search_min(int *N, int *cheapest, int size) {
    int min = INFINI;
    int min_index = -1;
    for (int i = 0; i < size; i++) {
        if (cheapest[i] < min && N[i] == 0) {
            min_index = i;
            min = cheapest[i];
        }
    }
    return min_index;
}


struct maze prim(struct map map) {
    // Initialization of the sets
    int *N = malloc(map.width * map.height * sizeof(int));
    int *cheapest = malloc(map.width * map.height * sizeof(int));
    int *predecessors = malloc(map.width * map.height * sizeof(int));

    // Beginning of the building of those sets
    for (int v = 0; v < map.width * map.height; v++) {
        cheapest[v] = INFINI;
        predecessors[v] = -1;
        N[v] = 0;
    }

    // Initialization of the while loop
    int S = 0;
    cheapest[S] = 0;

    // Loop
    for (int i = 0; i < map.width * map.height; i++) {

        int v = search_min(N, cheapest, map.width * map.height);
        N[v] = 1; // Equivalent to remove v from N (0 equivalent to in, 1 equivalent to out)

        // In order to do the loop with the neighbors, we need to find them
        struct neighbors neighbors_v = find_neighbors(map, v);
        //Beginning of the loop
        for (int n = 0; n < 4; n++){
            // Check if its not equal to -1 (not a neighbor)
            if (neighbors_v.array_neighbors[n] != -1) {
                // Check if n belongs to N
                if (N[neighbors_v.array_neighbors[n]] == 0) {
                    // Check if weight of (v, n) < cheapest[n]
                    if (neighbors_v.array_cost[n] < cheapest[neighbors_v.array_neighbors[n]]) {
                        cheapest[neighbors_v.array_neighbors[n]] = neighbors_v.array_cost[n];
                        predecessors[neighbors_v.array_neighbors[n]] = v;
                    }
                }
            }
        }
    }

    // Determination of the total cost of the maze
    int total_cost = 0;

    for (int i = 0; i < map.width * map.height; i++) {
        total_cost += cheapest[i];
    }

    // Important to free N and cheapest
    free(N);
    free(cheapest);

    // Declaration of the maze
    struct maze final_maze = {map.width, map.height, predecessors, total_cost};

    return final_maze;

}


