#include "pacman.h"


#define NB_LIFE 5


void pacman_maze_make(char* file_name){
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int swap = 0;
     
     FILE* file = fopen(file_name, "r");

     if (file) {
         /* lire la premiere ligne avant EOF */
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break;
               } else if (c==',') {
                      swap = 1;
               } else if (!swap) {
                      rows_s[rows_i]=c;
                      rows_i++;
               } else {
                      cols_s[cols_i]= c;
                      cols_i++;
               }
               printf("%c", c);
         }
     }

     /* convertir le string en nombre */
     int rows = atoi(rows_s);
     int cols = atoi(cols_s);

     alloc_maze();
     int gost = 0;

     for (int i=0; i<rows; i++){
         for (int j=0; j < cols; j++){
             c = getc(file);

             if (c=='\n'){
                 c = getc(file);
             } else if (c == 'p'){
               start_row = i;
               start_col = j;
               current_row = i;
               current_col = j;
             } else if ( c == 'g'){
               gosts_start_pos[gost][0] = i;
               gosts_start_pos[gost][1] = j;
               gosts_pos[gost][0] = i;
               gosts_pos[gost][1] = j;
               gost++;
             }

             maze[i][j] = c;
         }
     }

     fclose(file);
}


void move_gosts(){
    int dplct;
    for (int g=0; g++; g<3){
        if (rand()%5==0){
            dplct = rand()%4;
        }
        else{
            int d_height = current_row - gosts_pos[g][0];
            int d_weight = current_col - gosts_pos[g][1];
            if (abs(d_height)> abs(d_weight)){
                if (d_height<0){
                    dplct = 0;
                }
                if (d_height>0){
                    dplct = 2;
                }
            }
            else{
                if (d_weight<0){
                    dplct = 1;
                }
                if (d_weight>0){
                    dplct = 3;
                }
            }
        }
        move_one_gost(g, dplct);
    }
}

void move_one_gost(int g, int dplct){
    switch (dplct)
    {
        case 0:
            if (gosts_pos[g][1] != 1){ //If the gost do not get out the maze
                gosts_pos[g][1] ++;
            }
            break;
        
        case 1:
            if (gosts_pos[g][0] != 1){ //If the gost do not get out the maze
                gosts_pos[g][0] ++;
            }
            break;

        case 2:
            if (gosts_pos[g][1] != rows-2){ //If the gost do not get out the maze
                gosts_pos[g][1] --;
            }
            break;

        case 3:
            if (gosts_pos[g][0] != cols-2){ //If the gost do not get out the maze
                gosts_pos[g][0] --;
            }
            break;
        default:
            break;
    }
}