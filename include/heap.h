#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Node Structure
*/
struct node {
    // ID of the node
    int value;
    // Current cost of the node
    int cost;
    // Pointer to its left child
    struct node *left;
    // Pointer to its right child
    struct node *right;
    // Pointer to its parent node
    struct node *parent;
};

/**
 * @brief Heap Structure
*/
struct heap {
    // Number of nodes in the heap
    int nb_nodes;
    // Pointer to the root node of the heap
    struct node *root;
};


/**
 * @brief Binary implementation for int 
*/
struct bin {
    // The size of the representation of the number in binary
    int size;
    // The representation of an int in binary
    // The int in the i index represents the bit of power i
    int *nb_bin;
};

/**
 * @brief Decimal to Binary convert Function
*/
struct bin dec_to_bin(int a);


/**
 * @brief Finding the father of node n Function
*/
struct node *finding_father(int n, struct heap heap);


/**
 * @brief Function that order the tree when inserting an element
*/
void order_heap_insert(struct node *moving, struct heap *heap);


/**
 * @brief Insert Function
*/
void insert(int cout, struct heap *heap);


/**
 * @brief Function that order the tree when extracting an element
*/
void order_heap_extract_min(struct node *moving, struct heap *heap);


/**
 * @brief Extract_min Function
*/
int extract_min(struct heap *heap);


/**
 * @brief This is the print function with its auxiliary function
*/

void print_heap_aux(struct node *root, int level) ;
void print_heap(struct heap *heap) ;

#endif