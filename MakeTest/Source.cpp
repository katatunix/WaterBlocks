#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_FILE "..\\WaterBlocks.inp"

void main()
{
	const int M = 100;
	const int N = 100;

	srand(time(NULL));

	FILE* f = fopen(TEST_FILE, "wt");

	fprintf(f, "%d %d\n", M, N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int val = 0;
			//if (rand() % 100 == 0) val = 1;
			//val = rand() % 150;
			val = 1000;
			fprintf(f, "%d ", val);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	printf("FINISHED!!!");
	getch();
}
