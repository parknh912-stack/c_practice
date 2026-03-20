//정올 1462 보물섬 , BFS https://jungol.co.kr/problem/1462

#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_N (50+2)

/*전역 변수 & 배열*/
typedef struct _node {
	int r, c;
}node;

typedef struct _queue {
	int front;
	int rear;
	node data[125000];
}Queue;

node dir[4] = {
	{-1,0},
	{1,0},
	{0,-1},
	{0,1}
};

int R, C;					//맵 크기
char** map = NULL;			//map 2차원 배열
int** visited = NULL;		//방문표시 2차원배열
Queue queue;				//queue 선언
int result = INT_MIN;


/*함수 선언*/
void getInputMem();
void freeMem();
void inputData();
void printData();
void BFS();
void putBFSonebyone();


/*메인함수*/
int main() {
	getInputMem();
	inputData();
	//printData();
	putBFSonebyone();
	printf("%d\n", result-1);
	freeMem();
	return 0;
}


/*이하 함수 정의*/
void getInputMem() {
	(void)scanf("%d %d", &R, &C);
	map = (char**)calloc(R, sizeof(char*));
	visited = (int**)calloc(R, sizeof(int*));
	if (map == NULL || visited == NULL) exit(1);

	map[0] = (char*)calloc(R * C, sizeof(char));
	visited[0] = (int*)calloc(R * C, sizeof(int));
	if (map[0] == NULL || visited[0] == NULL) exit(1);

	for (int i = 1; i < R; ++i) {
		map[i] = map[0] + i * C;
		visited[i] = visited[0] + i * C;
	}
}


void freeMem() {
	free(map[0]);
	map[0] = NULL;
	free(map);
	map = NULL;
	free(visited[0]);
	visited[0] = NULL;
	free(visited);
	visited = NULL;
}

void inputData() {
	char temp[MAX_N] = { 0 };
	for (int i = 0; i < R; ++i) {
		(void)scanf("%s", temp);
		for (int j = 0; j < C; ++j) {
			map[i][j] = temp[j];
		}
	}
}

void printData() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}

/*
시작점 : n개 -> 1개씩 사용
인접 : 상하좌우 + 육지사이에서만 이동
종료점 : 없음. 완주해야함
큐 : r,c
방문표시 : visited 2차원배열
*/
void BFS() {
	int nR, nC;
	int next_distance;
	node curr;

	while (queue.front != queue.rear) {
		curr = queue.data[queue.front++];
		for (int i = 0; i < 4; ++i) {
			nR = curr.r + dir[i].r;
			nC = curr.c + dir[i].c;
			next_distance = visited[curr.r][curr.c] + 1;
			if ((nR >= 0) && (nR < R) && (nC >= 0) && (nC < C)) {
				if ((map[nR][nC] == 'L') && (visited[nR][nC] == 0)) {

					visited[nR][nC] = next_distance;
					queue.data[queue.rear++] = (node){ nR,nC };
				}
			}
		}
		if (result < visited[curr.r][curr.c])
			result = visited[curr.r][curr.c];
	}
}

void putBFSonebyone() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == 'L') {
				queue.front = queue.rear = 0;
				memset(visited[0], 0, sizeof(int) * R * C);
				visited[i][j] = 1;
				queue.data[queue.rear++] = (node){ i,j };
				BFS();
			}
		}
	}
}

#endif // 1