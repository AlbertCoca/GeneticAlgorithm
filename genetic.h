#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUM_GENES 37
#define NUM_CITIES 38
#define BARCELONA 3
#define POPULATION_SIZE 10

int* randomIndividual();
void printIndividual(int* indi);
int* crossover_PB(int* parent1, int* parent2);
int** generatePopulation();
int cost(int* individu, int costTable[][NUM_CITIES]);
