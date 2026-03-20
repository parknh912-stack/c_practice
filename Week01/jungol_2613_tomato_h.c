//정올 - 2613 토마토(고) https://jungol.co.kr/problem/2613

#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N (1000+1)

int map[MAX_N][MAX_N];
int R, C;
typedef struct _node {
	int r, c;
}node;
node Queue[MAX_N * MAX_N];
int front, rear;
int empty = 0;

/*Input : Tomato positino & EnQueue & count Empty*/
void inputData() {
	front = rear = 0;
	(void)scanf(" %d %d", &C, &R);
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			(void)scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				Queue[rear++] = (node){ i,j };
			}
			if (map[i][j] == -1)
				empty++;
		}
	}
}


int dR[4] = { -1,1,0,0 };
int dC[4] = { 0,0,-1,1 };	//상하좌우

/*
1. n개의 시작점이 Quene에는 익은 토마토(1)이 들어가 있음. (rear >0)

*/
int BFS(void) {
	int nR, nC, i;
	node curr = { 0,0 };
	while (front != rear) {
		curr = Queue[front++];
		for (i = 0; i < 4; ++i) {
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];
			if ((nR > 0) && (nR <= R) && (nC > 0) && (nC <= C) && (map[nR][nC] == 0)) {
				Queue[rear++] = (node){ nR,nC };
				map[nR][nC] = map[curr.r][curr.c] + 1;
			}
		}
	}
	if ((rear + empty) < (R * C))
		return -1;
	return map[curr.r][curr.c]-1;
}

int main(void) {
	inputData();

	printf("%d\n", BFS());
	return 0;
}
#endif

//void printData() {
//	for (int i = 1; i <= R; ++i) {
//		for (int j = 1; j <= C; ++j) {
//			printf("%d ", map[i][j]);
//		}
//		printf("\n");
//	}
//}