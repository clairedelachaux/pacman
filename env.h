#ifndef ENV
#define ENV

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

char** maze;
char** maze_init;
int rows;
int cols;
int start_row;
int start_col;
int current_row;
int current_col;
int next_row;
int next_col;
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
void maze_reset();
void move_gosts();
int move_one_gost(int g, int dplct);
void maze_render();


#endif

