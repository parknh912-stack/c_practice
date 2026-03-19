//백준 - 바이러스 #2606
#if 0
#define MAX_N (100+1)
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(a) sizeof(a)/sizeof((a)[0])
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


int adjM[MAX_N][MAX_N];
int adjL[MAX_N][MAX_N];
int visited[MAX_N];
int V, E;

int count = 0;

void inputDataM(void) {
	int from, to;
	(void)scanf("%d", &V);
	(void)scanf("%d", &E);
	for (int i = 1; i <= E; ++i) {
		(void)scanf("%d %d", &from, &to);
		adjM[from][to] = 1;
		adjM[to][from] = 1;
	}
}

void inputDataL(void) {
	for (int from = 1; from <= V; ++from) {
		int index = 2;
		for (int to = 1; to <= V; ++to) {
			if (adjM[from][to] == 1) {
				adjL[from][1]++;
				adjL[from][index] = to;
				index++;
			}
		}
	}
}

void testM(int L) {
	++count;
	for (int i = 1; i <= V; ++i) {
		if ((adjM[L][i] == 1) && (visited[i] == 0)) {
			visited[i] = 1;
			testM(i);
		}
	}
}

int main() {

	inputDataM();


	count = 0;
	visited[1] = 1;
	testM(1);
	printf("%d\n", count - 1);
	return 0;
}
#endif