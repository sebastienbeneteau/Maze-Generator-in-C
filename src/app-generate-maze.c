#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "maze.h"
#include "prim.h"

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
    struct maze my_maze = prim(map_test);


    print_maze(my_maze);
    
    // Generate Image
    generate_image(my_maze, argv[1]);

    // Important to free the heap
    free(map_test.array_edges);
    free(my_maze.predecessor);

    return 0;

}