#include <stdio.h>
#include <stdlib.h>
#include "maze.h"



void print_maze(struct maze m) {

    // VERY IMPORTANT : when you see # instead of \033[7m \033[m, its because i got a problem when I print the maze.
    // Some White blocks disappear when i replace it. I dont know why but with the #, it works really well.

    // Print the top border
    printf("\033[7m \033[m");
    for (int i = 0; i < m.width; i++) {
        printf("\033[7m \033[m");
        printf("\033[7m \033[m");
    }
    printf("\n");

    // Print the maze
    for (int i = 0; i < m.height; i++) {
        printf("\033[7m \033[m");
        for (int j = 0; j < m.width - 1; j++) {
            
            // Check if there is a path between node i and node i+1
            if (m.predecessor[i * m.width + j] == i * m.width + j + 1 ||
                m.predecessor[i * m.width + j + 1] == i * m.width + j) {
                printf("  ");
            } else {
                printf(" ");
                printf("\033[7m \033[m");
            }
        }
        
        // Print the last node of the line
        printf(" ");
        // Print the right border of the map
        printf("\033[7m \033[m\n");

        // Print the vertical walls
        if (i < m.height - 1) {
            printf("#");
            for (int j = 0; j < m.width; j++) {

                // Check if there is a path between node i and node i+width
                if (m.predecessor[i * m.width + j] == (i + 1) * m.width + j ||
                    m.predecessor[(i + 1) * m.width + j] == i * m.width + j) {
                    printf(" ");
                } else {
                    printf("\033[7m \033[m");
                }
                printf("\033[7m \033[m");
            }
            printf("\n");
        }
    }

    // Print the bottom border
    printf("#");
    for (int i = 0; i < m.width; i++) {
        printf("\033[7m \033[m");
        printf("\033[7m \033[m");
    }
    printf("\n");
}


void generate_image(struct maze m, char *filename) {
    // Opening of the file
    FILE *p_file = fopen(filename, "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", filename);
        exit(EXIT_FAILURE);
    }

    // Writing in the file of the first two lines
    fprintf(p_file, "P1\n");
    fprintf(p_file, "%d %d\n", m.width, m.height);

    // 1 stands for Wall, 0 stands for a Space
    // Beginning of the writing of the maze with the first border
    fprintf(p_file, "1 ");
    for (int i = 0; i < m.width; i++) {
        fprintf(p_file, "1 ");
        fprintf(p_file, "1 ");
    }
    fprintf(p_file, "\n");

    // Writing of the maze
    for (int i = 0; i < m.height; i++) {
        fprintf(p_file, "1 ");
        for (int j = 0; j < m.width - 1; j++) {
            
            // Check if there is a path between node i and node i+1
            if (m.predecessor[i * m.width + j] == i * m.width + j + 1 ||
                m.predecessor[i * m.width + j + 1] == i * m.width + j) {
                fprintf(p_file, "0 ");
                fprintf(p_file, "0 ");
            } else {
                fprintf(p_file, "0 ");
                fprintf(p_file, "1 ");
            }
        }
        
        // Writing of the last node of the line
        fprintf(p_file, "0 ");
        // Writing of the right border of the map
        fprintf(p_file, "1 ");

        // For the vertical walls
        if (i < m.height - 1) {
            fprintf(p_file, "1 ");
            for (int j = 0; j < m.width; j++) {

                // Check if there is a path between node i and node i+width
                if (m.predecessor[i * m.width + j] == (i + 1) * m.width + j ||
                    m.predecessor[(i + 1) * m.width + j] == i * m.width + j) {
                    fprintf(p_file, "0 ");
                } else {
                    fprintf(p_file, "1 ");
                }
                fprintf(p_file, "1 ");
            }
            fprintf(p_file, "\n");
        }
    }

    // Writing of the bottom border
    fprintf(p_file, "1 ");
    for (int i = 0; i < m.width; i++) {
        fprintf(p_file, "1 ");
        fprintf(p_file, "1 ");
    }
    fprintf(p_file, "\n");

    fclose(p_file);
}


