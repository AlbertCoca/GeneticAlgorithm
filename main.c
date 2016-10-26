#include <stdio.h>
#include <string.h>
#include "genetic.h"

#define MAX_LINE_LEN 500
#define NUM_CITIES 38
#define MAX_LEN_NAME 20

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

int main(){
	srand(7);
	int costTable[NUM_CITIES][NUM_CITIES] = {0};
	char names [NUM_CITIES][MAX_LEN_NAME];
	char line[MAX_LINE_LEN];
	int i, j;

	FILE *fp;
	fp = fopen("EurCapitals.csv", "r");

	printf("Reading names...\n");
	fgets(line, MAX_LINE_LEN, fp);
	getNames(line, names);
	getValues(fp, costTable);


	for(i=0; i<NUM_CITIES; i++){
		printf("%s\n", names[i]);
	}

	printf("Reading values...\n");
	
	printf("Checking...\n");
	for(i=0; i<NUM_CITIES; i++){
		printf("%d\n", costTable[36][i]);
	}
	int *v1 = randomIndividual();
	printIndividual(v1);
	int *v2 = randomIndividual();
	printIndividual(v2);

	int *vc = crossover_PB(v1,v2);
	printIndividual(vc);
	
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
