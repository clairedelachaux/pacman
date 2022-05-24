#include "stdlib.h"
#include "stdio.h"
#include"pacman.h"
#include"time.h"

int main(){
    srand(time(NULL));
    make_maze("mazepackman.txt");
    maze_render();
    initializeQ();
    initialize_state();
    int done;
    for(int i = 0; i<10; i++){
        int k=0;
        done = 0;
        nb_food = 292;
        nb_life = 5;
        current_col = start_col;
        current_col = start_col;
        s = 0;
        maze_reset();
        for(int g=0; g<3; g++){
            gosts_pos[g][0] = gosts_start_pos[g][0];
            gosts_pos[g][1] = gosts_start_pos[g][1];
            gosts_last_case[g] = ' ';
        }
        while(!done && k<10){
            done = next_step(s);
            k++;
        }
        printf("%d\t%d\t%d\t%d\t%d, \n", i, k, done, nb_life, nb_food);
    }
    free_Q();
}
