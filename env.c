#include "env.h"


#define NB_LIFE 5



void alloc_maze(){
     maze = malloc(rows * sizeof(char*));
     for(int i=0; i<rows; i++) {
         maze[i] = malloc(cols * sizeof(char*));
     }
     maze_init = malloc(rows * sizeof(char*));
     for(int i=0; i<rows; i++) {
         maze_init[i] = malloc(cols * sizeof(char*));
     }
}

void make_maze(char* file_name){
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int swap = 0;
     int nb_food = 0;
     
     FILE* file = fopen(file_name, "r");

     if (file) {
         // lire la premiere ligne avant EOF
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
         }
     }

     // convertir le string en nombre
    rows = atoi(rows_s);
    cols = atoi(cols_s);
    alloc_maze();

    int gost = 0;
    for (int i=0; i<rows; i++){
        for (int j=0; j < cols; j++){
             c = getc(file);
             if (c=='\n' || c==13){
                 c = getc(file);
                 c=getc(file);
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
               gosts_last_case[gost] = ' ';
               gost++;
             }
             else if(c == '.'){
                 nb_food++;
             }
             maze[i][j] = c;
             maze_init[i][j] = c;
         }
     }

     fclose(file);
}

void maze_render(){
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", maze[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}

void maze_reset(){
    for (int i=0; i<rows; i++){
        for(int j =0; j<cols; j++){
            maze[i][j] = maze_init[i][j];
            //print("%d, %d %d %d", i, j, maze[i][j], maze_init[i][j]);
        }
    }
}

void maze_init_render(){
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", maze_init[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}

void move_gosts(){
    int dplct;
    for (int g=0; g<3; g++){
        if (rand()%5==0){
            dplct = rand()%4;
        }
        else{
            int d_height = current_row - gosts_pos[g][0];
            int d_weight = current_col - gosts_pos[g][1];
            if (abs(d_height)> abs(d_weight)){
                if (d_height<0){
                    dplct = north;
                }
                if (d_height>0){
                    dplct = south;
                }
            }
            else{
                if (d_weight<0){
                    dplct = west;
                }
                if (d_weight>0){
                    dplct = east;
                }
            }
        }
        if(move_one_gost(g, dplct)){
            return ;
        };
    }
}

int move_one_gost(int g, int dplct){
    int i = gosts_pos[g][0];
    int j = gosts_pos[g][1];
    switch (dplct)
    {
        case west:
            if (gosts_pos[g][1] != 1){ //If the gost do not get out the maze
                if (gosts_last_case[g]=='p'){
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = ' ';
                }else{
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = gosts_last_case[g];
                }
                gosts_pos[g][1] --;
                if (maze[gosts_pos[g][0]][gosts_pos[g][1]]== 'g'){
                    gosts_pos[g][1] ++;
                }
            }
            break;
        
        case north:
            if (gosts_pos[g][0] != 1){ //If the gost do not get out the maze
                if (gosts_last_case[g]=='p'){
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = ' ';
                }else{
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = gosts_last_case[g];
                }
                gosts_pos[g][0] --;
                if (maze[gosts_pos[g][0]][gosts_pos[g][1]]== 'g'){
                    gosts_pos[g][0] ++;
                }
            }
            break;

        case east:
            if (gosts_pos[g][1] != cols-2){ //If the gost do not get out the maze
                if (gosts_last_case[g]=='p'){
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = ' ';
                }else{
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = gosts_last_case[g];
                }
                gosts_pos[g][1] ++;
                if (maze[gosts_pos[g][0]][gosts_pos[g][1]]== 'g'){
                    gosts_pos[g][1] --;
                }
            }
            break;

        case south:
            if (gosts_pos[g][0] != rows-2){
                if (gosts_last_case[g]=='p'){
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = ' ';
                }else{
                    maze[gosts_pos[g][0]][gosts_pos[g][1]] = gosts_last_case[g];
                } //If the gost do not get out the maze
                gosts_pos[g][0] ++;
                if (maze[gosts_pos[g][0]][gosts_pos[g][1]]== 'g'){
                    gosts_pos[g][0] --;
                }
            }
            break;
        default:
            break;
    }
    if (maze[gosts_pos[g][0]][gosts_pos[g][1]]== 'p'){
        for (int gost = 0; gost<3; gost++){
            gosts_last_case[gost] = ' ';
            maze[gosts_pos[gost][0]][gosts_pos[gost][1]] = gosts_last_case[gost];
            gosts_pos[gost][0] = gosts_start_pos[gost][0];
            gosts_pos[gost][1] = gosts_start_pos[gost][1];
        }
        maze[gosts_pos[g][0]][gosts_pos[g][1]] = ' ';
        return 1;
    }
    gosts_last_case[g] = maze[gosts_pos[g][0]][gosts_pos[g][1]]; 
    maze[gosts_pos[g][0]][gosts_pos[g][1]] = 'g';
    return 0;
}
