#include "genetic.h"

int* randomIndividual(){
	int r = rand()%NUM_GENES;
	int i;
	int *rIndi;
	rIndi = (int*)malloc(sizeof(int)*NUM_GENES);
	
	for (i = 0; i <= NUM_GENES; i++) {     // fill array
	    if(i != BARCELONA) rIndi[i] = i;
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
		printf("%d\n", costTable[s][d]);
		s = d;
	}
	d = BARCELONA;
	printf("%d\n", costTable[s][d]);
	c+=costTable[s][d];
	printf("%d\n", c);
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
				p2[i] = -1;
				break;
			}
		}
	}
	printIndividual(child);
	for(i=0;i<NUM_GENES; i++){
		if(p2[i]>-1){
			for(j=0; j<NUM_GENES; j++){
				if(child[j] == -1){
					child[j] = p2[i];
					break;
				}
			}
		}
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
