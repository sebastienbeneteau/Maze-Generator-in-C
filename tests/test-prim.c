#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "prim.h"
#include "maze.h"

#define INFINI 2147483647 //Represents the infinity with the maximum number for 32 bits integers

int main(int argc, char *argv[]){
    // testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name!\n");
        exit(EXIT_FAILURE);
    }

    // Initialization of the test map
    struct map map_test = load(argv[1]);

    // Print of predecessors
    struct maze maze = prim(map_test);
    for (int i = 0; i < map_test.width * map_test.height; i++){
        printf("%d\n", maze.predecessor[i]);
    }
    printf("%d\n", maze.total_cost);

    //Compare with others map and predecessors by looking at tests_maze.txt

    // Free the allocate memory in the heap
    free(map_test.array_edges);
    free(maze.predecessor);

    return 0;
}