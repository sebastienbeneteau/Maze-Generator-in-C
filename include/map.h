

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>



/**
 *  @brief Structure representing edges
*/
struct edges{
    /* cost of the edge starting from the node and going to the node below it*/
    int down;
    /* cost of the edge starting from the node and going to the node at its right*/
    int right;
};

/**
 *  @brief Structure representing map
*/
struct map{
    int height;
    int width;
    /*The pointer to edges in the map structure points to a dynamically allocated memory region that can be assimilated to an array of edges values*/
    struct edges *array_edges;
};

/**
 * @brief Load function declaration
*/
struct map load(char *filename);

/**
 * @brief Print map function declaration
*/
void print_map(struct map new_map);

/**
 * @brief Structure representing neighbors
*/
struct neighbors {
    // nb field containing the number of neighbors of 𝑛
    int nb;
    //array of 4 int values containing the numbers of the nodes that are neighbors of 𝑛
    int array_neighbors[4];
    //array of 4 int values containing the cost of the edges to go from 𝑛 to its neighbors
    int array_cost[4];
};

/**
 * @brief Declaration of find_neighbors function
*/
struct neighbors find_neighbors(struct map my_map, int node);



#endif