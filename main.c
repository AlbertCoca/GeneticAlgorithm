#include <stdio.h>
#include <string.h>
#include "genetic.h"

void getNames(char *line,  char names[][MAX_LEN_NAME]);
void getValues(FILE *fp, int costTable[][NUM_CITIES]);

int findIndexOfChar(char* s, char c, int n){
	int i, offset = -1;
	for(i=0; i<n; i++){
		const char *ptr = strchr(s+offset+1, c);
		if(ptr == NULL) return -1;
		offset = ptr - s;
	}
	return offset;
}

void help(){
	printf("You must specify the crossover and the Mutation Type: \n");
	printf("First parameter must contain the crossover Type:\n");
	printf("-B\t For Pointed Based crossover\n");
	printf("-O\t For Order crossover\n");
	//printf("-H\t For Heuristic crossover\n");
	printf("Second parameter must contain the mutation Type:\n");
	printf("-E\t For Exange crossover\n");
	printf("-I\t For Inverse crossover\n");
	printf("\nExample: ./ga B I\n");
}

int main(int argc, char const *argv[])
{
	crossover cross;
	mutation mut;
	if(argc < 3){
		help();
		abort();
	}
	switch (argv[1][0])
	{
		case 'B':
			cross = &crossover_PB;
			break;
		case 'O':
			cross = &crossover_OX;
			break;
		//case 'H':
		//	cross = &crossover_H;
		//	break;
		default:
			help();
			abort();
			break;
	}
	switch (argv[2][0])
	{
		case 'E':
			mut = &mutation_E;
			break;
		case 'I':
			mut = &mutation_I;
			break;
		default:
			help();
			abort();
			break;
	}
	srand(time(NULL));
	int costTable[NUM_CITIES][NUM_CITIES] = {0};
	char names [NUM_CITIES][MAX_LEN_NAME];
	char line[MAX_LINE_LEN];
	int i, j;

	FILE *fp;
	fp = fopen("EurCapitals.csv", "r");

	fgets(line, MAX_LINE_LEN, fp);
	getNames(line, names);
	getValues(fp, costTable);

	int *v1 = randomIndividual();
	//printIndividual(v1);
	int *v2 = randomIndividual();
	//printIndividual(v2);
	int *cv = crossover_H(v1, v2, costTable);

	//checkConsistence(cv);
	int* best = GA(costTable, cross, mut);
	//printf("%d\n", cost(best, costTable));
	//printIndividual(best);

	printNames(best, names);
	
	return 0;
}

void getNames(char *line,  char names[][MAX_LEN_NAME]){
	int i;

	int start = findIndexOfChar(line, ',', 1)+1;
	int end = findIndexOfChar(line, ',', 2);
	for(i=0; end != -1 ;){
		memcpy( names[i], &line[start], end - start );
		names[i][end] = '\0';
		i++;
		start = findIndexOfChar(line, ',', i+1)+1;
		end = findIndexOfChar(line, ',', i+2);
	}
	end = strlen(line);
	memcpy( names[i], &line[start], end - start );
}

void getValues(FILE *fp, int costTable[][NUM_CITIES]){
	int i, j;
	char line[MAX_LINE_LEN];
	for(i=0; fgets(line, MAX_LINE_LEN, fp);i++){
		int start = findIndexOfChar(line, ',', 1)+1;
		int end = findIndexOfChar(line, ',', 2);
		for(j=0; end != -1;){
			char buff[20] = {'\0'};
			memcpy(buff, &line[start], end - start );
			costTable[i][j] = atoi(buff);
			j++;
			start = findIndexOfChar(line, ',', j+1)+1;
			end = findIndexOfChar(line, ',', j+2);
		}
		char buff[20] = {'\0'};
		end = strlen(line);
		memcpy(buff, &line[start], end - start );
		costTable[i][j] = atoi(buff);

	}

}
