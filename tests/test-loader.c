#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct map load(char *filename){

    FILE *p_file = fopen(filename, "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", filename);
        exit(EXIT_FAILURE);
    }

    // read dimensions on first line
    int width         = 0;
    int height        = 0;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d %d\n", &width, &height);

     if (fscanf_result != 2) {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    // Declaration of new_map 
    struct map new_map;

    // Put width and height values in new_map
    new_map.width = width;
    new_map.height = height;

    // Allocate dynamic memory to struct edges
    new_map.array_edges = calloc(width*height, sizeof(struct edges));
  
    // read following lines
    // each line is composed of two integer values
    int below = 0;
    int right = 0;


    for (int i = 0; i < height * width; i++) {
        fscanf_result = fscanf(p_file, "%d %d", &below, &right);

        //Checking the syntax of the line
        if (fscanf_result != 2) {
            fprintf(stderr, "Line %d is not syntactically correct!\n", i + 2);
            exit(EXIT_FAILURE);
        }

        //Assigning edges values to the new_map edges array
        new_map.array_edges[i].down = below;
        new_map.array_edges[i].right = right;

    }

    fclose(p_file);
    return new_map;
};


int main(int argc, char *argv[]){
    // testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name!\n");
        exit(EXIT_FAILURE);
    }
    struct map new_map = load(argv[1]);
    print_map(new_map);
    free(new_map.array_edges);

    return 0;
}