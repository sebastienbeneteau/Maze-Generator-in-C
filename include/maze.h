

#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Structure representing maze
*/
struct maze {
    // the width and the height of the map
    int width;
    int height;
    //array, declared as a pointer, predecessors of int values such that predecessors[i] is the number of the node that is the predecessor of node i in the minimum spanning tree
    int *predecessor;
    //the total cost of the maze (i.e. the sum of all edges in the corresponding minimum spanning tree)
    int total_cost;
};

/**
 * @brief Print_maze Function
*/
void print_maze(struct maze my_maze);

/**
 * @brief Generate_image Function
*/
void generate_image(struct maze my_maze, char *filename);


#endif