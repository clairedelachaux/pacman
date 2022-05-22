#include "pacman.h"

#define eps 0.1
#define gamma 0.9
#define alpha 0.99 
#define true 1
#define false 0
#define NB_ACTIONS 4
#define NB_STATES 2048

void initializeQ()
{
    Q = malloc(NB_STATES * sizeof(float*)); //nombre d'etat = nb colonnes * nb lignes
     for(int i=0; i<rows*cols; i++) {
         Q[i] = malloc(NB_ACTIONS * sizeof(float));
         for(int j=0; j< NB_ACTIONS; j++){
             Q[i][j]=0;
         }
     }
}

void afficher_Q(){
    for(int i=0; i<NB_STATES; i++){
        for (int j=0; j<NB_ACTIONS; j++){
            printf("%f ", Q[i][j]);
        }
        printf("\n");
    }

}

int eps_greedy(int s){
    int a = north;
    float nb_alea = (1.*rand())/RAND_MAX;
    if (nb_alea<eps){
        a = rand()%4;
        //printf(" greedy ");
    }
    else{;
        for (int a_i=1; a_i< NB_ACTIONS; a_i++){
            if (Q[s][a_i]> Q[s][a]){
                a = a_i;
            }
            if(Q[s][a_i] == Q[s][a]){
                if (1.*rand()/RAND_MAX<0.5){
                    a = a_i;
                }
            }
        }
    }
    return a;
}

void calculate_new_state(int a){
    int i = current_row;
    int j = current_col;
    switch (a)
    {
        case east:
            if ((j=!1) && (maze[i][j-1] == ' ')){
                new_state(i, j-1);
                
            }
            break;
        
        case north:
            if ((i=!1) && (maze[i-1][j] == ' ')){
                new_state(i-1, j);
            }
            break;

        case west:
            if ((j=! (cols-2)) && (maze[i][j+1] == ' ')){
                new_state(i, j+1);
            }
            break;

        case south:
            if ((i=!(rows-2)) && (maze[i+1][j] == ' ')){
                new_state(i+1, j);
            }
            break;
        default:
            break;
    }
}

void new_state(int i, int j){
    if(maze[i-1][j]=='+'){
        state[0] = true;
    }
    if(maze[i][j-1]=='+'){
        state[1] = true;
    }
    if(maze[i+1][j]=='+'){
        state[2] = true;
    }
    if(maze[i][j+1]=='+'){
        state[3] = true;
    }
    state[4] = nearest_target(i, j);
    int k=0;
    while((i+k<rows)&&(maze[i+k][j]!='g')){
        k++;
    }
    if(i+k==rows){
        state[5+south] = false;
    }
    k=0;
    while((i-k>=0)&&(maze[i-k][j]!='g')){
        k--;
    }
    if(i-k==-1){
        state[5+north] = false;
    }
    k=0;
    while((j+k<cols)&&(maze[i][j+k]!='g')){
        k++;
    }
    if(i+k==rows){
        state[5+east] = false;
    }
    k=0;
    while((i-k>=0)&&(maze[i][j-k]!='g')){
        k--;
    }
    if(i+k==-1){
        state[5+west] = false;
    }
}

void min(int*t, int n, int* val_min, int* ind_min){
    for (int k=0; k<n; k++){
        if (t[k]<*val_min){
            *val_min = t[k];
            *ind_min = k;
        }
        if (t[k]==*val_min && rand()%2==0){
            *val_min = t[k];
            *ind_min = k;
        }
    }
}

int nearest_target(int i, int j){
    int nearest_pill[4];
    int k=0;
    while(maze[i+k][j]==' '){
        k++;
    }
    if (maze[i+k][j]=='+'){
        nearest_pill[south] = 50;
    }
    if(maze[i+k][j]=='.'){
        nearest_pill[south] = k;
    }
    if(maze[i+k][j]=='g'){
        nearest_pill[south] = 100;
    }
    k=0;
    while(maze[i-k][j]==' '){
        k++;
    }
    if (maze[i+k][j]=='+'){
        nearest_pill[north] = 50;
    }
    if(maze[i+k][j]=='.'){
        nearest_pill[north] = k;
    }
    if(maze[i+k][j]=='g'){
        nearest_pill[north] = 100;
    }
    k=0;
    while(maze[i][j+k]==' '){
        k++;
    }
    if (maze[i][j+k]=='+'){
        nearest_pill[west] = 50;
    }
    if(maze[i][j+k]=='.'){
        nearest_pill[west] = k;
    }
    if(maze[i][j+k]=='g'){
        nearest_pill[west] = 100;
    }
    k=0;
    while(maze[i][j-k]==' '){
        k++;
    }
    if (maze[i][j-k]=='+'){
        nearest_pill[east] = 50;
    }
    if(maze[i][j-k]=='.'){
        nearest_pill[east] = k;
    }
    if(maze[i][j-k]=='g'){
        nearest_pill[east] = 100;
    }
    int ind_min = north;
    min(nearest_pill, 4, &nearest_pill[north], &ind_min);
    return ind_min;
}

int is_trapped(int* state){
    if(!state[north]&&(!state[north+5])){
        return false;
    }
    if(!state[south]&&(!state[south+5])){
        return false;
    }
    if(!state[east]&&(!state[east+5])){
        return false;
    }
    if(!state[west]&&(!state[west+5])){
        return false;
    }
    return true;
}
