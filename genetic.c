#include "genetic.h"

int* randomIndividual(){
	int r = rand()%NUM_GENES;
	int i, j=0;
	int *rIndi;
	rIndi = (int*)malloc(sizeof(int)*NUM_GENES);
	
	for (i = 0; i <= NUM_GENES; i++) {     // fill array
	    if(i != BARCELONA){
	    	rIndi[j] = i;
	    	j++;
	    }

	}

	for (i = 0; i < NUM_GENES; i++) {    // shuffle array
	    int temp = rIndi[i];
	    int randomIndex = rand() % NUM_GENES;

	    rIndi[i]           = rIndi[randomIndex];
	    rIndi[randomIndex] = temp;
	}
	return rIndi;	
	
}
int cost(int* individu, int costTable[][NUM_CITIES]){
	int i, c=0;
	int s = BARCELONA; //Source
	int d; 		   //Destination
	for(i=0; i<NUM_GENES; i++){
		d = individu[i];
		c+=costTable[s][d];
		s = d;
	}
	d = BARCELONA;
	c+=costTable[s][d];
	return c;
	
}

int** generatePopulation(){
	int** p;
	p = (int**) malloc(sizeof(int*)*POPULATION_SIZE);
	int i;
	for(i=0; i<POPULATION_SIZE; i++){
		p[i] = randomIndividual();
	}
	return p;
}

//Inversion Mutation
void mutation_I(int *indi){
	int i;
	int start = rand()%NUM_GENES;
	int end = rand()%(NUM_GENES-start)+start;
	int aux = 0;
	for(i=0; i<(end-start)/2; i++){
		aux = indi[start+i];
		indi[start+i] = indi[end-i-1];
		indi[end-i-1] = aux;
	}
}



//Position Based Crossover
int* crossover_PB(int* parent1, int* parent2){
	int i, j;
	int *child = (int*)malloc(sizeof(int)*NUM_GENES);
	int *p2 = (int*)malloc(sizeof(int)*NUM_GENES);
	memcpy(p2, parent2, sizeof(int)*NUM_GENES);
	for(i=0; i<NUM_GENES; i++)child[i] = -1;
	
	int start = rand()%NUM_GENES;
	int end = rand()%(NUM_GENES-start)+start;

	for(i=start; i<end; i++){
		child[i] = parent1[i];
		for(j=0; j<NUM_GENES; j++){
			if(p2[j] == child[i]){
				p2[j] = -1;
				break;
			}
		}
	}
	for(i=0;i<NUM_GENES; i++){
		if(p2[i]!=-1){
			for(j=0; j<NUM_GENES; j++){
				if(child[j] == -1){
					child[j] = p2[i];
					break;
				}
			}
		}
	}
	free(p2);
	return child;
		
}

void printIndividual(int* indi){
	int i;
	for (i = 0; i < NUM_GENES; i++) {     // fill array
	    printf("%d, ", indi[i]);
	}
	printf("\n");
}

int checkConsistence(int* indi){
	int i, j, t;
	for(i=0; i<NUM_GENES; i++){
		t = 0;
		for(j=0; j<NUM_GENES; j++){
			if(i == indi[j]) t++;
		}
		if(t > 1){
			printf("Inconsistent Individual\n");
			return 0;
		}
	}
	printf("Consistent Individual\n");
	return 1;
}

void printNames(int* indi, char names[][MAX_LEN_NAME]){

	int i;
	printf("Barcelona, ");
	for(i=0; i<NUM_GENES; i++){
		printf("%s, ", names[indi[i]]);
	}
	printf("Barcelona \n");
}

//TODO maybe there is a better way to do this
int* GA(int costTable[][NUM_CITIES]){

	int** population = generatePopulation();
	int** newPopu;
	
	newPopu = (int**) malloc(sizeof(int*)*POPULATION_SIZE);
	int i, j;
	int* min1;
	int* min2;
	int minCost1, minCost2;
	for(j=0; j<NUM_GENERATIONS; j++){


		int actCost=0;

		minCost1 = cost(population[0], costTable);
		minCost2 = cost(population[1], costTable);
		min1 = population[0];
		min2 = population[1];


		if (minCost2 < minCost1){
			int aux = minCost1;
			minCost1 = minCost2;
			minCost2 = minCost1;

			int* aux2 = min1;
			min1 = min2;
			min2 = aux2;
		}

		for(i=2; i<POPULATION_SIZE; i++){
			actCost = cost(population[i], costTable);
			if(actCost < minCost1){
				minCost2 = minCost1;
				min2 = min1;
				minCost1 = actCost;
				min1 = population[i];
			}
			else if (actCost < minCost2){
				minCost2 = actCost;
				min2 = population[i];
			}
		}
		newPopu[0] = min1;
		newPopu[1] = min2;
		newPopu[2] = crossover_PB(min1, min2);
		for(i=3; i<(POPULATION_SIZE-3) / 2 +1; i++){
			newPopu[i] = crossover_PB(min1, population[i]);
		}

		for(i=(POPULATION_SIZE-3) / 2 +1; i<POPULATION_SIZE; i++){
			newPopu[i] = crossover_PB(min1, population[i]);
		}
		for(i=2; i<POPULATION_SIZE; i++){
			mutation_I(newPopu[i]);
		}
		int** aux = population;
		population = newPopu;
		newPopu  = aux;
		printf("%d\n", cost(min1, costTable));
	}
	return min1;

}