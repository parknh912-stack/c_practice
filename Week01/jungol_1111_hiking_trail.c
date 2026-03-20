//정올 1111 등산로 https://jungol.co.kr/problem/1111
#define J_1111 2
//내가 만든 코드임
#if J_1111 == 1
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
node Queue[MAX_N * MAX_N * MAX_N];	//Queue의 크기를 충분히 크게
int front, rear;

int map[MAX_N][MAX_N];
int cost[MAX_N][MAX_N];
int N, eR, eC;

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
	printf("front = %d\n", front);
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


//Top 부터 하는 방법 by. 문경한
#if J_1111 == 2
#define _CRT_SECURE_NO_WARNINGS
#define MAX_COST 999999
#include <stdio.h>
#include <stdlib.h>

typedef struct _pos {
	int r;
	int c;
}position;

typedef struct _queue {
	int front;
	int rear;
	position data[20000];
}Queue;

position dir[4] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

int N; // 산 크기
int result = MAX_COST; // 결과값
int** map; // 고도
int** costs; // 각 위치까지 도달하는데 필요한 최단 비용을 저장하는 배열

Queue queue; // 큐
position end_pos; // 목적지 좌표

void set(int x, int y, int t); //cost 갱신 + 큐에 저장
void BFS();
void getInput();
void setup_startPoint(); // 시작 위치를 큐에 저장

int main() {
	//freopen("mountain.txt", "r", stdin);
	getInput();
	setup_startPoint();
	BFS();
	printf("%d", costs[end_pos.r][end_pos.c]);
}

void BFS() {
	position data; // 다음 위치를 받는 구조체
	int curr_r, curr_c; // 현재 위치를 저장하는 변수
	int nR, nC; // 다음 위치를 저장하는 변수
	int curr_height; // 현재 위치의 고도
	int next_height; // 다음 위치의 고도
	int cost; // 다음 위치로 이동할 때 필요한 코스트
	int curr_cost; // 현재 위치까지의 코스트 합

	while (queue.front != queue.rear) {
		data = queue.data[queue.front++];
		curr_r = data.r;
		curr_c = data.c;

		for (int i = 0; i < 4; ++i) {
			nR = curr_r + dir[i].r;
			nC = curr_c + dir[i].c;

			if (0 < nR && nR < N && 0 < nC && nC < N) {
				curr_cost = costs[curr_r][curr_c];
				curr_height = map[curr_r][curr_c];
				next_height = map[nR][nC];

				// 비용 계산
				if (curr_height == next_height) { // 평지
					cost = curr_cost;
				}
				else if (curr_height < next_height) { // 오르막길
					cost = curr_cost + ((next_height - curr_height) * (next_height - curr_height));
				}
				else { // 내리막길
					cost = curr_cost + (curr_height - next_height);
				}

				// 이 루트 비용이 더 작으면 cost를 갱신 + 큐에 다음 위치 저장
				if (costs[nR][nC] > cost) {
					set(nR, nC, cost);
				}
			}
		}
	}
}

void set(int r, int c, int t) {
	queue.data[queue.rear++] = (position){ r, c };
	costs[r][c] = t;
}

void getInput() {
	scanf("%d", &N);
	scanf("%d %d", &end_pos.r, &end_pos.c);

	N += 2;

	map = (int**)calloc(N, sizeof(int*));
	costs = (int**)calloc(N, sizeof(int*));
	if (map == NULL || costs == NULL) exit(1);

	for (int i = 0; i < N; ++i) {
		map[i] = (int*)calloc(N, sizeof(int));
		costs[i] = (int*)calloc(N, sizeof(int));
		if (map[i] == NULL || costs[i] == NULL) exit(1);
	}

	for (int i = 1; i < N - 1; ++i) {
		for (int j = 1; j < N - 1; ++j) {
			scanf("%d", &map[i][j]);
			costs[i][j] = MAX_COST;
		}
	}
}

// 시작 위치(외곽) -> 큐에 저장
void setup_startPoint() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == 0 || i == N - 1 || j == 0 || j == N - 1) set(i, j, 0);
		}
	}
}
#endif // 0


// by 민지님
#if J_1111 == 3

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 등산로
#define MAX_N (100 + 2)
#define INF (10000)
int map[MAX_N][MAX_N];
int cost[MAX_N][MAX_N]; //해당 좌표까지의 비용 저장
int N;
int dR, dC; // 산 정상 좌표
typedef struct _node {
	int r;
	int c;
}node;
node Queue[MAX_N * MAX_N * 10];
int front, rear;

void inputData(void) {
	(void)scanf("%d", &N);
	(void)scanf("%d %d", &dR, &dC);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cost[i][j] = INF;
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			(void)scanf("%d", &map[i][j]);
			if ((i == 1) || (i == N) || (j == 1) || (j == N)) {
				Queue[rear++] = (node){ i, j };
				cost[i][j] = map[i][j] * map[i][j];
			}
		}
	}
}

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int BFS(void) {
	int nR, nC, i;
	node curr;
	int nCost; // curr -> (nR, nC)로 가는 추가비용

	while (front != rear) {
		curr = Queue[front++];
		if (curr.r == dR && curr.c == dC) continue; // 정상에 도착했으면 탐색 더 X

		for (i = 0; i < 4; i++) {
			nR = curr.r + dx[i];
			nC = curr.c + dy[i];

			if (nR < 1 || nR > N || nC < 1 || nC > N) continue; // 경계 검사

			//nCost = map[curr.r][curr.c] - map[nR][nC];
			if (map[nR][nC] <= map[curr.r][curr.c]) {    // 내리막, 평지
				nCost = map[curr.r][curr.c] - map[nR][nC];
			}
			else {    // 오르막
				nCost = (map[nR][nC] - map[curr.r][curr.c]) * (map[nR][nC] - map[curr.r][curr.c]);
			}

			if (cost[nR][nC] > cost[curr.r][curr.c] + nCost) {
				cost[nR][nC] = cost[curr.r][curr.c] + nCost;
				Queue[rear++] = (node){ nR, nC };
			}
		}
	}
	return cost[dR][dC];
}
int main(void) {
	inputData();
	printf("%d\n", BFS());
	printf("front = %d\n", front);
	return 0;
}
#endif // 1
