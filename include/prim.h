#ifndef PRIM_H
#define PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/**
 * @brief Prim's MST algorithm
*/
struct maze prim(struct map map);


/**
 * @brief Simple algorithm of minimum
*/
int search_min(int *N, int *cheapest, int size);




#endif