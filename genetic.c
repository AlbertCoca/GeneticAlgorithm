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

//Exange Mutation
void mutation_E(int *indi){
	int pos1 = rand()%NUM_GENES;
	int pos2 = rand()%NUM_GENES;
	int aux = 0;

	aux = indi[pos1];
	indi[pos1] = indi[pos2];
	indi[pos2] = aux;

}

//Position Based Crossover
int* crossover_OX(int* parent1, int* parent2, int costTable[][NUM_CITIES]){
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

int* crossover_PB(int* parent1, int* parent2, int costTable[][NUM_CITIES]){
	int i, j;
	int *child = (int*)malloc(sizeof(int)*NUM_GENES);
	int *p2 = (int*)malloc(sizeof(int)*NUM_GENES);
	memcpy(p2, parent2, sizeof(int)*NUM_GENES);
	for(i=0; i<NUM_GENES; i++)child[i] = -1;
	
	int num_pos = rand()%(NUM_GENES)-1;

	for(i=0; i<num_pos; i++){
		int rPos = rand()%(NUM_GENES);
		//printf("%d,", rPos);
		child[rPos] = parent1[rPos];
		for(j=0; j<NUM_GENES; j++){
			if(p2[j] == child[rPos]){
				p2[j] = -1;
				break;
			}
		}
	}
	//printf("\n");
	//printIndividual(child);

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

int* crossover_H(int* parent1, int* parent2, int costTable[][NUM_CITIES]){
	int *child = (int*)malloc(sizeof(int)*NUM_GENES);
	int *p1 = (int*)malloc(sizeof(int)*NUM_GENES);
	int *p2 = (int*)malloc(sizeof(int)*NUM_GENES);
	int *freePos = (int*)malloc(sizeof(int)*NUM_GENES);
	int i, j;
	memcpy(p1, parent1, sizeof(int)*NUM_GENES);
	memcpy(p2, parent2, sizeof(int)*NUM_GENES);
	for(i=0; i<NUM_GENES; i++)child[i] = -1;
	for(i=0; i<NUM_GENES; i++)freePos[i] = i;
	freePos[BARCELONA] = -1;

	//Starting City
	int sCity = BARCELONA;
	while(sCity==BARCELONA){
		sCity = rand()%(NUM_GENES);
	}
	child[0] = sCity;
	freePos[sCity] = -1;
	for(j=1; j<NUM_GENES; j++){
	
		sCity = child[j-1];
		freePos[sCity] = -1;
		//Parets City position
		int p1cp;
		int p2cp;
		for(i=0; i<NUM_GENES; i++){
			if(p1[i] == sCity)p1cp = i;
			if(p2[i] == sCity)p2cp = i;
		}
		for(i=0; i<NUM_GENES; i++){
			p1[i] = parent1[(p1cp+i)%NUM_GENES];
			p2[i] = parent2[(p2cp+i)%NUM_GENES];
		}
		
		//printf("%d \n", p1cp);
		//printf("%d \n", p2cp);
		//printf("%d \n", sCity);
		//printIndividual(p1);
		//printIndividual(p2);

		int p1Valid = 1;
		int p2Valid = 1;

		for(i=0; i<j; i++){
			if (p1[1] == child[i]) p1Valid = 0;
			if (p2[1] == child[i]) p2Valid = 0;
		}

		if(p1Valid && p2Valid){
			if(costTable[sCity][p1[1]] <= costTable[sCity][p2[1]]) child[j] = p1[1];
			else child[j] = p2[1];
		}
		else if(p1Valid)child[j] = p1[1];
		else if(p2Valid)child[j] = p2[1];
		else{
			for(i=0; i<NUM_GENES; i++){
				if(freePos[i] != -1) child[j] = freePos[i];
			}
		}
		//printIndividual(child);
	}
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
int* GA(int costTable[][NUM_CITIES], crossover cross, mutation mut){

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
		newPopu[2] = cross(min1, min2, costTable);
		for(i=3; i<(POPULATION_SIZE-3) / 2 +1; i++){
			newPopu[i] = cross(min1, population[i], costTable);
		}

		for(i=(POPULATION_SIZE-3) / 2 +1; i<POPULATION_SIZE; i++){
			newPopu[i] = cross(min1, population[i], costTable);
		}
		for(i=2; i<POPULATION_SIZE; i++){
			mut(newPopu[i]);
		}
		int** aux = population;
		population = newPopu;
		newPopu  = aux;
		printf("%d\n", cost(min1, costTable));
	}
	return min1;

}
