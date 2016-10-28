#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUM_GENES 37
#define NUM_CITIES 38
#define BARCELONA 3
#define POPULATION_SIZE 100
#define NUM_GENERATIONS 1000
#define MAX_LINE_LEN 500
#define NUM_CITIES 38
#define MAX_LEN_NAME 20

int* randomIndividual();
void printIndividual(int* indi);
int* crossover_PB(int* parent1, int* parent2);
int** generatePopulation();
int cost(int* individu, int costTable[][NUM_CITIES]);
void mutation_I(int *indi);
int* GA(int costTable[][NUM_CITIES]);
int checkConsistence(int* indi);
void printNames(int* indi, char names[][MAX_LEN_NAME]);
