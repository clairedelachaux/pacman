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
     for(int i=0; i<NB_STATES; i++) {
         Q[i] = malloc(NB_ACTIONS * sizeof(float));
         for(int j=0; j< NB_ACTIONS; j++){
             Q[i][j]=0;
         }
     }
}

void initialize_state(){
    int* state = malloc(10*sizeof(int));
    new_state(current_row, current_col, state);
    s = calc_state(state);
}

void afficher_Q(){
    for(int i=0; i<NB_STATES; i++){
        for (int j=0; j<NB_ACTIONS; j++){
            printf("%f ", Q[i][j]);
        }
    }
    printf("\n");
}

int eps_greedy(int s){
    int a = north;
    float nb_alea = (1.*rand())/RAND_MAX;
    if (nb_alea<eps){
        a = rand()%4;
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

int calculate_new_state(int a, int* n_state){
    int i = current_row;
    int j = current_col;
    int out;
    printf("%d", a);
    switch (a)
    {
    case west:
        if ((j=!1) && (maze[i][j-1] == ' ')){
            out = new_state(i, j-1, n_state);
        }else{out = new_state(i, j, n_state);}
    break;
        
    case north:
        if ((i=!1) && (maze[i-1][j] == ' ')){
            out = new_state(i-1, j, n_state);
            }else{out = new_state(i, j, n_state);}
            break;

        case east:
            if ((j=! (cols-2)) && (maze[i][j+1] == ' ')){
                out = new_state(i, j+1, n_state);
            }
            else{out = new_state(i, j, n_state);}
            break;

        case south:
            if ((i=!(rows-2)) && (maze[i+1][j] == ' ')){
                out = new_state(i+1, j, n_state);
            }else{out = new_state(i, j, n_state);}
            break;
        default:
            break;
    }
    return out;
}

int new_state(int i, int j, int* n_state){
    if(maze[i-1][j]=='+'){
        n_state[0] = true;
    }else{
        n_state[0] = false;
    }
    if(maze[i][j-1]=='+'){
        n_state[1] = true;
    }else{
        n_state[1] = false;
    }
    if(maze[i+1][j]=='+'){
        n_state[2] = true;
    }else{
        n_state[2] = false;
    }
    if(maze[i][j+1]=='+'){
        n_state[3] = true;
    }else{
        n_state[3] = false;
    }
    n_state[4] = nearest_target(i, j);
    int k=0;
    while((i+k<rows)&&(maze[i+k][j]!='g')){
        k++;
    }
    if(i+k>=rows){
        n_state[5+south] = false;
    }else{
        n_state[5+south] = true;
    }
    k=0;
    while((i-k>=0)&&(maze[i-k][j]!='g')){
        k++;
    }
    if(i-k==-1){
        n_state[5+north] = false;
    }else{
        n_state[5+north] = true;
    }
    k=0;
    while((j+k<cols)&&(maze[i][j+k]!='g')){
        k++;
    }
    if(j+k==cols){
        n_state[5+west] = false;
    }else{
        n_state[5+west] = true;
    }
    k=0;
    while((i-k>=0)&&(maze[i][j-k]!='g')){
        k++;
    }
    if(i-k==-1){
        n_state[5+east] = false;
    }else{
        n_state[5+east] = true;
    }
    n_state[10] = is_trapped(state);
    for(int k=0; k<10; k++){
        printf("%d- ", n_state[k]);
    }
    return calc_state(n_state);
}

int calc_state(int* s){
    return 2*(s[0]+ 2*(s[1]+ 2*(s[2]+ 2*(s[3]+ 4*(s[4]+ 2*(s[5]+ 2*(s[6]+ 2*(s[8]+ 2*(s[9]+ 2*s[7])))))))));
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

float max_a(int s_prime, int a){
    float M = Q[s_prime][0];
    for (int k=1; k<4; k++){
        if(Q[s_prime][k]>M){
            M = Q[s_prime][k];
        }
        if((Q[s_prime][k]==M)&&(rand()%2==0)){
            M = Q[s_prime][k];
        }
    } 
    return M;
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
    if (maze[i-k][j]=='+'){
        nearest_pill[north] = 50;
    }
    if(maze[i-k][j]=='.'){
        nearest_pill[north] = k;
    }
    if(maze[i-k][j]=='g'){
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

int is_trapped(int* s){
    if(!s[north]&&(!s[north+5])){
        return false;
    }
    if(!s[south]&&(!s[south+5])){
        return false;
    }
    if(!s[east]&&(!s[east+5])){
        return false;
    }
    if(!s[west]&&(!s[west+5])){
        return false;
    }
    return true;
}

int next_step(){
    int a = eps_greedy(s);
    switch (a)
    {
    case north:
        next_row = current_row-1;
        next_col = current_col;
        break;
    
    case south:
        next_row = current_row+1;
        next_col = current_col;
        break;

    case west:
        next_col = current_col-1;
        next_row = current_row;
        break;
    
    case east:
        next_col = current_col+1;
        next_row = current_row;
        break;
    
    default:
        break;
    }
    int reward = 0;
    switch (maze[next_row][next_col])
    {
    case 'g':
        reward = -100;
        nb_life--;
        for (int g=0; g<3; g++){
            if (gosts_last_case[g]=='p'){
                maze[gosts_pos[g][0]][gosts_pos[g][1]] = ' ';
            }else{
                maze[gosts_pos[g][0]][gosts_pos[g][1]] = gosts_last_case[g];
            }
            gosts_last_case[g] = ' ';
            gosts_pos[g][0] = gosts_start_pos[g][0];
            gosts_pos[g][1] = gosts_start_pos[g][1];
        }
        break;

    case '+':
        reward = -10;
        next_col = current_col;
        next_row = current_row;
    break;

    case '.':
        reward = 10;
        nb_food--;
    break;
    
    default:
        break;

    }
    if (nb_food==0){
        return 1;
    }
    if (nb_life==0){
        return -1;
    }
    maze[current_row][current_col] = ' ';
    int s_prime = calculate_new_state(a, state);
    printf("%d%d", s, s_prime);
    Q[s][a] += alpha*(reward + gamma*(max_a(s_prime, a)-Q[s][a]));
    current_col = next_col;
    current_row = next_row;
    maze[current_row][current_col]= 'p';
    move_gosts();
    s = s_prime;
    printf("\n");
    return 0;
}

void free_Q(){
    for(int i=0; i<NB_STATES; i++){
        free(Q[i]);
    }
    free(Q);
}
