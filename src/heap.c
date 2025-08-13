#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heap.h"


struct bin dec_to_bin(int a) {

    // Initialization of variables
    int cpt = 1;
    int var_a = a;
    
    // Calculate size
    while (var_a / 2 > 0) {
        var_a = var_a / 2;
        cpt = cpt + 1;
    }

    // Initialization of the binary representation
    int a_rep[cpt];

    // Building of the representation

    // Initialization of the variables
    var_a = a;
    int i = 0;

    // Beginning of the loop until i equals cpt
    while (i < cpt) {
        // If var_a is even, we add a 0 in the right place in its binary representation
        if (var_a % 2 == 0) {
            var_a = var_a / 2;
            a_rep[i] = 0;

            // Dont forget to increment i
            i = i + 1;
        } else {   // If its not even, we add a 1
            var_a = var_a / 2;
            a_rep[i] = 1;

            // Dont forget to increment i
            i = i + 1;
        }
    }

    // Definition of our bin
    struct bin a_bin = {cpt, a_rep};

    return a_bin;
}


struct node *finding_father(int n, struct heap heap) {
    // Initialization
    struct bin n_bin = dec_to_bin(n);
    struct node *p_father = heap.root;

    // Ensure that n_bin.size is at least 2 to avoid out-of-bounds access
    if (n_bin.size <= 2) {
        return p_father;
    }

    // Start of the loop with this values because we dont consider the first and the last element of n_bin.nb_bin, binary representation of n in a int pointer
    for (int i = n_bin.size - 2; i >= 1; i--) {

        // We go to the right if we get a 1 in the binary representation
        if (n_bin.nb_bin[i] == 1) {
            p_father = p_father->right;
        } else {     // Or we go to the left if we have a 0
            p_father = p_father->left;
        }
    }

    return p_father;
}

void order_heap_insert(struct node *moving, struct heap *heap) {
    // Stop condition : if the cost of moving is greater than his parent's cost
    // OR moving is actually the root of the heap (no parent)
    if (moving->parent == NULL || moving->cost > moving->parent->cost) {
        //printf("done");
    } else {
        int c = moving->cost;
        int v = moving->value;

        // Switch of the costs and values
        moving->cost = moving->parent->cost;
        moving->parent->cost = c;

        moving->value = moving->parent->value;
        moving->parent->value = v;

        // Recursive call of the function
        order_heap_insert(moving->parent, heap);
    }

}

void insert(int cout, struct heap *heap) {
    //Initialization of the new node
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = heap->nb_nodes + 1;
    new_node->cost = cout;
    new_node->left = NULL;
    new_node->right = NULL;

    // Case if the heap is empty
    if (heap->root == NULL){
        heap->root = new_node;
        heap->nb_nodes = heap->nb_nodes + 1;

    }
    else {

        // Find the parent of this new_node


        struct node *father = finding_father(heap->nb_nodes + 1, *heap);

        // Consider new_node as the son of this parent
        if (father->left == NULL) {
            father->left = new_node;
        } else {
            father->right = new_node;
        }

        // Consider this father as the parent of new_node
        new_node->parent = father;

        // Order the tree
        order_heap_insert(new_node, heap);

        // Increase the number of nodes in the heap
        heap->nb_nodes = heap->nb_nodes + 1;
    }
}

// THAT IS A TEST FOR A RECURSIVE ALGORITHM TO ORDER A TREE AFTER EXTRACT BUT IT DOESN'T WORK
// AFTER ALL MY EFFORTS, I CANT SUPPRESS IT SO I PUT IT IN TEXT

/*void order_heap_extract_min(struct node *moving, struct heap *heap) {
    if (moving == NULL) {
        return; 
    }

    if (moving->left == NULL && moving->right == NULL) {
        // No child nodes
        return;
    } else if (moving->right == NULL || moving->left->cost < moving->right->cost) {
        // Only left child or left child is smaller
        if (moving->cost > moving->left->cost) {
            int c = moving->cost;
            int v = moving->value;

            // Switch of the costs and values

            moving->cost = moving->left->cost;
            moving->left->cost = c;

            moving->value = moving->left->value;
            moving->left->value = v;

            order_heap_extract_min(moving->left, heap);
        }
    } else if (moving->left->cost < moving->right->cost) {
        // Right child is smaller
        int c = moving->cost;
        int v = moving->value;

        // Switch of the costs and values

        moving->cost = moving->right->cost;
        moving->right->cost = c;

        moving->value = moving->right->value;
        moving->right->value = v;

        order_heap_extract_min(moving->right, heap);
    }
}*/

void order_heap_extract_min(struct node *moving, struct heap *heap) {


    while ((moving->left != NULL && moving->right != NULL) && (moving->cost > moving->left->cost || moving->cost > moving->right->cost)) {

        // Declaration of moving_temp
        struct node *moving_temp;

        // Find the true next position of moving (the node)
        if (moving->right == NULL) {  // Be careful with the NULL case
            moving_temp = moving->left;
        } else if (moving->right->cost > moving->left->cost) {
            moving_temp = moving->left;
        } else {
            moving_temp = moving->right;
        }

        // Swap the cost and values of the nodes in order to swap them completely
        int c = moving->cost;
        int v = moving->value; 

        moving->cost = moving_temp->cost;
        moving_temp->cost = c;

        moving->value = moving_temp->value;
        moving_temp->value = v;

        // Dont forget to change the moving node pointer
        moving = moving_temp;

    }
}

int extract_min(struct heap *heap) {

    // Ensure that the root isnt NULL
    if (heap->root == NULL) {
        return 0;
    }

    // The value of the root we want to retrieve
    int v_root = heap->root->cost;

    // Beginning of the extraction

    // Find the father first
    struct node *father_last_node = finding_father(heap->nb_nodes, *heap);

    // The switch between the last node and the root

    if (father_last_node != NULL) {   // Be careful with the NULL case
        if (father_last_node->right != NULL) {  // Be careful with the NULL case
            
            //Switch of values and cost with the root
            heap->root->cost = father_last_node->right->cost;
            heap->root->value = father_last_node->right->value;

            // Free the allocate memory
            free(father_last_node->right);

            father_last_node->right = NULL;

        } else if (father_last_node->left != NULL) {  // Be careful with the NULL case

            // Switch of values and cost with the root
            heap->root->cost = father_last_node->left->cost;
            heap->root->value = father_last_node->left->value;

            // Free the allocate memory
            free(father_last_node->left);

            father_last_node->left = NULL;
        }
        
    }

    // Order the tree
    order_heap_extract_min(heap->root, heap);

    // Decrement the number of nodes in the heap
    heap->nb_nodes -= 1;

    return v_root;
}



// I WANTED TO SEE THE REPRESENTATION OF MY HEAP OR TREE SO I CODED THIS PRINT_HEAP FUNCTION WITH ITS AUXILIARY FUNCTION TO MAKE IT RECURSIVE
// I INVITE YOU TO TEST IT. IT IS A NICE WAY TO REPRESENT AND VERIFY THE QUALITY OF A HEAP, OF THE INSERT AND EXTRACT FUNCTIONS
// ROTATE YOUR HEAD BY 90 DEGREES IN THE TRIGONOMETRIC WAY TO VISUALIZE IT

void print_heap_aux(struct node *root, int level) {
    // Stop Condition : when the node (called root) equals NULL : when we dont have children anymore
    if (root == NULL)
        return;

    // We go to the right on the screen and the right side of the tree is up on the screen (with the head rotation on the right).
    // So, firstly, we have to print the right side of the tree (tree or sub-trees)
    print_heap_aux(root->right, level + 1);

    // We put distances between the cost in order to make sure to distinguish the tree
    // The more profound we are in the tree, the more you have to give space in the horizontal axis (turn vertical with the head rotation)
    for (int i = 0; i < level; i++)
        printf("   ");

    // Print of the cost
    printf("%d\n", root->cost);

    // We go to the right on the screen and the left side of the tree is down on the screen (with the head rotation on the left).
    // So, lastly, we have to print the left side of the tree (tree or sub-trees) 
    print_heap_aux(root->left, level + 1);
}

void print_heap(struct heap *heap) {

    // Be careful at the NULL case
    if (heap == NULL || heap->root == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    // Highlight the beginning of the heap
    printf("Heap:\n");

    // Call of the auxiliary function at the start of the heap : the root
    print_heap_aux(heap->root, 0);
}



