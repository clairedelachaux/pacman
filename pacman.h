#ifndef PACMAN
#define PACMAN
#include "env.h"

int state[10];
int state_curr;

void initializeQ();

int eps_greedy(int s);

void afficher_Q();

void calculate_new_state(int a);

void min(int*t, int n, int* val_min, int* ind_min);

void new_state(int i, int j);

int nearest_target(int i, int j);

float** Q;

#endif