//정올 1111 등산로 https://jungol.co.kr/problem/1111

#if 1
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <limits.h>
	#define MAX_N (100+2)	//주의


	/*node 및 전역 배열, 변수 선언*/
	typedef struct _node {
		int r, c;
	}node;
	node Queue[MAX_N*MAX_N*MAX_N];	//Queue의 크기를 충분히 크게
	int front, rear;

	int map[MAX_N][MAX_N];
	int cost[MAX_N][MAX_N];
	int N,eR,eC;

	int dR[4] = { -1,1,0,0 };
	int dC[4] = { 0,0,-1,1 };	//상하좌우


	/*함수 선언*/
	void inputData();
	void printData();
	void startPointEnQueue();
	int costProcessing(int start, int end);
	int BFS();

	/*메인 함수*/
	int main() {
		//(void)freopen("J1111.txt", "r", stdin);
		inputData();
		startPointEnQueue();
		printf("%d\n", BFS());
		return 0;
	}

	/*이하 함수 정의*/
	void inputData() {
		(void)scanf(" %d", &N);
		(void)scanf("%d %d", &eR, &eC);

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				(void)scanf("%d", &map[i][j]);
				cost[i][j] = INT_MAX;	
			}
		}
	}

	void printData(int S, int N, int(*map)[MAX_N]) {
		for (int i = S; i <= N; ++i) {
			for (int j = S; j <= N; ++j) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	/*바깥쪽 0, N번쨰들을 Queue에 삽입*/
	void startPointEnQueue() {
		front = rear = 0;
		for (int i = 1; i <= N; ++i) {
			Queue[rear++] = (node){ 0, i };
			Queue[rear++] = (node){ N + 1, i };
		}
		for (int i = 1; i <= N; ++i) {
			Queue[rear++] = (node){ i, 0 };
			Queue[rear++] = (node){ i, N + 1 };
		}
	}

	int costProcessing(int start, int end) {
		if (start >= end)	//내리막길 + 평지
			return start - end;
		return ((end - start) * (end - start));//오르막길
	}

	/*
	BFS 함수
	시작점 : n개 외곽 -> 미리 Queue에 넣어둠
	인접 : 상하좌우
	종료점 : 1개 -> 정상 (eR, eC)
	큐 : r,c
	방문표시 : map data 변경 (1씩 증가)
	*/
	int BFS() {
		int nR, nC, i;
		int curr_cost;
		int end_cost = INT_MAX;
		int add_cost;
		node curr;
		
		while (front != rear) {
			curr = Queue[front++];
			if ((curr.r == eR) && (curr.c == eC)) continue;
			for (i = 0; i < 4; ++i) {
				nR = curr.r + dR[i];
				nC = curr.c + dC[i];

				curr_cost = cost[curr.r][curr.c];
				add_cost = costProcessing(map[curr.r][curr.c], map[nR][nC]);

				if ((nR > 0) && (nR <= N) && (nC > 0) && (nC <= N))
				{
					if ((curr_cost + add_cost) < cost[nR][nC]) {
						cost[nR][nC] = curr_cost + add_cost;
						Queue[rear++] = (node){ nR,nC };
					}
				}
			}
		}
		return cost[eR][eC];
	}
#endif // 1
