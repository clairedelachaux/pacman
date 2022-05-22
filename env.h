#ifndef ENV
#define ENV

#include <stdio.h>
#include <stdlib.h>


char** maze;
int rows;
int cols;
int start_row;
int start_col;
int current_row;
int current_col;
int gosts_pos[3][2];
char gosts_last_case[3];
int gosts_start_pos[3][2];



enum direction{
    north,
    west,
    south,
    east
};

void alloc_maze();
void make_maze(char* file_name);
void move_gosts();
void move_one_gost(int g, int dplct);
void maze_render();


#endif

