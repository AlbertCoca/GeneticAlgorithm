#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUM_GENES 37
#define NUM_CITIES 38
#define BARCELONA 3
#define POPULATION_SIZE 100
#define NUM_GENERATIONS 10000	
#define MAX_LINE_LEN 500
#define NUM_CITIES 38
#define MAX_LEN_NAME 20
#define NUM_E_MUT 1	

typedef int* (*crossover)(int*, int*, int costTable[][NUM_CITIES]);
typedef void (*mutation)(int*);

//Initializing Functions
int* randomIndividual();
int** generatePopulation();

//Util Functions
void printIndividual(int* indi);
int checkConsistence(int* indi);
void printNames(int* indi, char names[][MAX_LEN_NAME]);

//Algorithm Functions
int cost(int* individu, int costTable[][NUM_CITIES]);
int* GA(int costTable[][NUM_CITIES], crossover cross, mutation mut);

//CrossOver Functions
int* crossover_OX(int* parent1, int* parent2, int costTable[][NUM_CITIES]);
int* crossover_PB(int* parent1, int* parent2, int costTable[][NUM_CITIES]);
int* crossover_H(int* parent1, int* parent2, int costTable[][NUM_CITIES]);

//Mutation Functions
void mutation_I(int *indi);
void mutation_E(int *indi);
