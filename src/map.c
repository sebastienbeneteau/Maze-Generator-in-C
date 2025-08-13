#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define INFINI 2147483647 //Represents the infinity with the maximum number for 32 bits integers


void print_map(struct map new_map){
    //We print firstly the height and width
    printf("%d %d\n", new_map.height, new_map.width);
    //We browse in the array edges and print down and right numbers
    for (int i = 0; i < new_map.height * new_map.width; i++) {
        printf("%d %d\n", new_map.array_edges[i].down, new_map.array_edges[i].right);
    }

};


struct neighbors find_neighbors(struct map my_map, int node) {
    int neighbor_up = -1;
    int neighbor_down = -1;
    int neighbor_right = -1;
    int neighbor_left = -1;

    // Declaration of the index of the neighbors with their respective tests

    // Neighbor above
    if (node >= my_map.width) {
        neighbor_up = node - my_map.width;
    };
    // Neighbor below
    if (node < (my_map.height - 1)*my_map.width) {
        neighbor_down = node + my_map.width;
    };
    // Neighbor right
    if (node % my_map.width != my_map.width - 1) {
        neighbor_right = node + 1;
    };
    // Neighbor left
    if (node % my_map.width != 0) {
        neighbor_left = node - 1;
    };

    // Beginning of the construction of the neighbors structure for node
    struct neighbors neighbors_node;

    // Cost of the edges
    neighbors_node.array_cost[0] = INFINI ;
    neighbors_node.array_cost[1] = INFINI ;
    neighbors_node.array_cost[2] = INFINI ;
    neighbors_node.array_cost[3] = INFINI ;

    // Below
    if (neighbor_down >= 0) {
        neighbors_node.array_cost[0] = my_map.array_edges[node].down;
    };
    // Right
    if (neighbor_right >= 0) {
        neighbors_node.array_cost[1] = my_map.array_edges[node].right;
    };
    // Above
    if (neighbor_up >= 0) {
        neighbors_node.array_cost[2] = my_map.array_edges[neighbor_up].down;
    };
    // Left
    if (neighbor_left >= 0) {
        neighbors_node.array_cost[3] = my_map.array_edges[neighbor_left].right;
    };

    // Declaration of a browse array in order to use for ()
    int browse_array[4] = {neighbor_down, neighbor_right, neighbor_up, neighbor_left};
    
    // Number of neighbors
    int k = 0;
    for (int i = 0; i < 4; i++) {
        if (browse_array[i] >= 0) {
            k++;
        }
    }
    neighbors_node.nb = k;

    // Array with the number of each neighbors of node
    for (int i = 0; i < 4; i++){
        // -1 indicates it has no neighbor in the i direction
        neighbors_node.array_neighbors[i] = browse_array[i];
    }
    
    // The two for () loop is kind of useless. I could have use one.
    // However, for a better understanding of the code, I chose to do it this way.

    return neighbors_node;
};






