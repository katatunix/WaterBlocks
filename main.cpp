#include <stdio.h>

#define FI "WaterBlocks.inp"
#define MAX (100 + 1)

int M, N;
int h[MAX][MAX];

int water[MAX][MAX];
bool markLoang[MAX][MAX];

int queueI[MAX * MAX]; // for loang
int queueJ[MAX * MAX]; // for loang

const int u[4] = { 0, 0, -1, 1 }; // direction X
const int v[4] = { 1, -1, 0, 0 }; // direction Y

void readInput() {
	FILE* f = fopen(FI, "rt");
	fscanf(f, "%d %d", &M, &N);
	for (int i = 1; i <= M; ++i)
		for (int j = 1; j <= N; ++j)
			fscanf(f, "%d", &(h[i][j]));
	fclose(f);
}

bool isBorder(int i, int j) {
	return i == 1 || i == M || j == 1 || j == N;
}

bool isInside(int i, int j) {
	return i >= 1 && i <= M && j >= 1 && j <= N;
}

/**
  * return true if the block (i, j, k)
  * can store water
  */
bool loang(int i, int j, int k) {
	for (int x = 1; x <= M; ++x)
		for (int y = 1; y <= N; ++y)
			markLoang[x][y] = false;
	markLoang[i][j] = true;
	queueI[1] = i;
	queueJ[1] = j;
	int first = 1, last = 1;
	bool result = true;
	while (first <= last) {
		i = queueI[first];
		j = queueJ[first];
		++first;
		for (int dir = 0; dir < 4; ++dir) {
			int iNext = i + u[dir];
			int jNext = j + v[dir];
			if (!isInside(iNext, jNext)) continue;

			// the block must be empty
			if (h[iNext][jNext] >= k) continue;

			// if we can travel to the border
			if (isBorder(iNext, jNext)) result = false;

			if (markLoang[iNext][jNext]) continue;
			markLoang[iNext][jNext] = true;
			++last;
			queueI[last] = iNext;
			queueJ[last] = jNext;
		}
	}

	return result;
}

void updateWater(int upToHeight) {
	for (int i = 2; i < M; ++i)
		for (int j = 2; j < N; ++j)
			if (markLoang[i][j])
				water[i][j] = upToHeight - h[i][j];
}


void solve() {
	for (int i = 2; i < M; ++i)
		for (int j = 2; j < N; ++j)
			water[i][j] = 0;

	for (int i = 2; i < M; ++i)
		for (int j = 2; j < N; ++j)
			if (water[i][j] == 0) {
				int k = h[i][j] + 1;
				while (loang(i, j, k)) {
					updateWater(k);
					++k;
				}
			}
}

void writeOutput() {
	int sum = 0;
	for (int i = 2; i < M; ++i)
		for (int j = 2; j < N; ++j)
			sum += water[i][j];

	printf("%d", sum);
}

int main() {
	readInput();
	solve();
	writeOutput();
	return 0;
}
