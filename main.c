#include "stdlib.h"
#include "stdio.h"
#include"env.h"

int main(){
    make_maze("mazepackman.txt");
    maze_render();
    move_gosts();
    maze_render();
}