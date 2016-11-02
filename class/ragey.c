#include <stdio.h>

#define TEAM_SIZE 6

typedef struct PERSON{
	float length;
	struct PERSON* next;
} PERSON;

PERSON* sort(PERSON to_sort[]);

int main(void)
{
	PERSON Ben = {1.99, NULL};
	PERSON Hella = {1.83, NULL};
	PERSON Jaap = {1.87, NULL};
	PERSON Jelle = {1.79, NULL};
	PERSON Martijn = {1.74, NULL};
	PERSON Wouter = {1.86, NULL};

	PERSON team[TEAM_SIZE] = {Ben, Hella, Jaap, Jelle, Martijn, Wouter};

	PERSON* line = sort(team);

	while(line != NULL)
	{
		printf("%.2f\n", line->length);
		line = line->next;
	}
	
	printf("\n\nThe program is done!\n\n\n");

	return 0;
}

PERSON* sort(PERSON to_sort[])
{

	PERSON biggest = {0.00, NULL};

	for (int j = 0; j < TEAM_SIZE; ++j)
	{
		if (to_sort[j].length >= biggest.length) {
			biggest = to_sort[j];
		}
	}
	
	printf("\n\n%.2f\n", biggest.length);

	// Basically I can sort. What's up next? 
	// I need to point the biggest to the previous biggest


	return 0;
} 


int const hello = 2;
hello = 3;

