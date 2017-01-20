#include <stdio.h>
#include <conio.h>
#include <cassert>

#include <Windows.h>

#define FI "WaterBlocks.inp"

#define _MAX 200
#define MAX (_MAX + 1)

int M, N;
int h[MAX][MAX];

int water[MAX][MAX];
bool markLoang[MAX][MAX];

int queueRow[MAX * MAX]; // for loang
int queueCol[MAX * MAX]; // for loang

int u[4] = { 0, 0, -1, 1 }; // direction X
int v[4] = { 1, -1, 0, 0 }; // direction Y

void readinput()
{
	FILE* f = fopen(FI, "rt");
	fscanf(f, "%d %d", &M, &N);
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fscanf(f, "%d", &(h[i][j]));
		}
	}
	fclose(f);
}

bool isBorder(int i, int j)
{
	return i == 1 || i == M || j == 1 || j == N;
}

bool isInside(int i, int j)
{
	return i >= 1 && i <= M && j >= 1 && j <= N;
}

// return true if the square (row, col, height) can store water
bool loang(int row, int col, int height)
{
	for (int i = 2; i < M; i++) for (int j = 2; j < N; j++)
	{
		markLoang[i][j] = false;
	}
	markLoang[row][col] = true;

	int first, last;
	first = last = 1;
	queueRow[1] = row;
	queueCol[1] = col;
	while (first <= last)
	{
		int r = queueRow[first];
		int c = queueCol[first];
		first++;
		for (int dir = 0; dir < 4; dir++)
		{
			int rNext = r + u[dir];
			int cNext = c + v[dir];
			
			if ( !isInside(rNext, cNext) ) continue;

			if (markLoang[rNext][cNext]) continue;

			if (h[rNext][cNext] >= height) continue; // the square must be empty

			if (isBorder(rNext, cNext)) return false; // we can travel to the border, so return false

			//if (water[rNext][cNext] > 0) return false;

			markLoang[rNext][cNext] = true;
			last++;
			queueRow[last] = rNext;
			queueCol[last] = cNext;
		}
	}

	return true;
}

void updateWater(int height)
{
	for (int i = 2; i < M; i++) for (int j = 2; j < N; j++)
	{
		if (markLoang[i][j])
		{
			water[i][j] = height - h[i][j];
			assert(water[i][j] > 0);
		}
	}
}

void solve()
{
	for (int i = 2; i < M; i++) for (int j = 2; j < N; j++)
	{
		water[i][j] = 0;
	}

	//--------------------------------------------------------------
	for (int i = 2; i < M; i++) for (int j = 2; j < N; j++)
	{
		if (water[i][j] == 0) // with water[i][j] > 0 we make sure that it no longer stores water
		{
			int k = h[i][j] + 1;
			while (loang(i, j, k))
			{
				updateWater(k);
				k++;
			}
		}
	}
	//--------------------------------------------------------------
}

void writeoutput()
{
	int sum = 0;
	for (int i = 2; i < M; i++) for (int j = 2; j < N; j++)
	{
		sum += water[i][j];
	}

	printf("%d\n", sum);
	
}

void main()
{
	unsigned long long start = GetTickCount();
	readinput();
	solve();
	writeoutput();
	unsigned long long end = GetTickCount();
	printf("time = %fs\n", (float)(end - start) / 1000.0);

	_getch();
}
