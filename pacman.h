#ifndef PACMAN
#define PACMAN
#include "env.h"

int state[10];
int s;
int nb_life;
int nb_food;
float** Q;

void initializeQ();

void initialize_state();

int eps_greedy(int s);

void afficher_Q();

int calculate_new_state(int a, int* n_state);

void min(int*t, int n, int* val_min, int* ind_min);

float max_a(int s_prime);

int calc_state(int* s);

int new_state(int i, int j, int* n_state);

int nearest_target(int i, int j);

int is_trapped(int* s);

int next_step();

void free_Q();

#endif
