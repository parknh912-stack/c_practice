//정올 1661 미로탈출로봇 https://jungol.co.kr/problem/1661

#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N (100+1)


/*node 및 전역 배열, 변수 선언*/
typedef struct _node {
	int r, c;
}node;
node Queue[MAX_N * MAX_N];	//10000
int front, rear;
int map[MAX_N][MAX_N];
int R, C;
int sR, sC, eR, eC;
int dR[4] = { -1,1,0,0 };
int dC[4] = { 0,0,-1,1 };	//상하좌우
int loop = 0;

/*함수 선언*/
void inputData();
int BFS(void);


/*메인 함수*/
int main() {
	inputData();
	printf("%d\n", BFS());
	//printf("%d\n", loop);
	return 0;
}

/*Input : R,C,sR,sC,eR,eC, map 정보*/
void inputData() {
	(void)scanf(" %d %d", &C, &R);
	(void)scanf(" %d %d %d %d", &sC, &sR, &eC, &eR);
	char temp[MAX_N] = { 0 };
	for (int i = 1; i <= R; ++i) {
		(void)scanf(" %s", temp + 1);
		for (int j = 1; j <= C; ++j) {
			map[i][j] = temp[j] - '0';	//char -> int
		}
	}
}


/* 
BFS 함수
시작점 : 1개
인접 : 상하좌우
종료점 : 1개
큐 : r,c
방문표시 : map data 변경 (1씩 증가)
*/
int BFS(void) {
	int nR, nC, i;
	int time;
	node curr;

	front = rear = 0;
	Queue[rear++] = (node){ sR,sC };
	map[sR][sC] = 1;

	if ((sR == eR) && (sC == eC)) return 0; //이미 도착점이면, 이동거리 0

	while (front != rear) {
		curr = Queue[front++];
		for (i = 0; i < 4; ++i) {
			loop++;
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];
			time = map[curr.r][curr.c] +1;	//개선. 1번만 참조해서, 변수에 저장 (4번 써야하므로, 참조를 최소화)
			if ((nR > 0) && (nR <= R) && (nC > 0) && (nC <= C)) {	//개선필요. 62번이나 반복해야하는데?
				if (map[nR][nC] == 0) {
					if ((nR == eR) && (nC == eC)) return time -1;	//위치는 여기가 낫다 + time에 바로 -1 박는게 연산이 더 적겠네
					Queue[rear++] = (node){ nR,nC };	//EnQueue
					map[nR][nC] = time;
				}
			}
		}
	}
	return -1;	//종료점 도달이 불가능한 경우 -1 반환
}



#endif // 1
