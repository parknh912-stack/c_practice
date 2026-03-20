#if 0
//정올 1078 저글링 방사능 오염 https://jungol.co.kr/problem/1078
#include "___AAA___.h"
#define MAX_N (100+1)
int R, C;		//map 사이즈 (행 , 열)
int sR, sC;		//공격 시작 위치
int map[MAX_N][MAX_N];	//최대 map 사이즈 배열
int cnt = 0;

/*BFS를 위한 Queue 생성*/
typedef struct _node {
	int r, c;
}node;
node Queue[MAX_N* MAX_N];
int front, rear;


/*EnQ DeQ, 근데 너무 짧으니, 그냥 함수 안쓰고 한줄씩 써도 된다.*/
void Enqueue(node data) {
	Queue[rear++] = data;
}
node DeQueue(node data) {
	return Queue[front++];
}


/*Input : juggling position*/
void inputData() {
	char temp[MAX_N] = { 0 };
	for (int i = 1; i <= R; ++i) {
		(void)scanf("%s", temp + 1);
		for (int j = 1; j <= C; ++j) {
			map[i][j] = temp[j] - '0';	//char -> int
			cnt += map[i][j];		//총 저글링 숫자
		}
	}
}


/*Print : For check input success*/
void printData() {
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

/*
1. 시작정점 EQ + 방문표시
2. Q에 데이터가 있다면 -> 정점 DQ + 인접 확인
3. 인접 있다면 -> 해당 좌표 EQ + 방문표시 (여기서 time으로 표시하면 1석2조)
4. 2~3을 반복 (Until (데이터가 더이상 없을 떄 = 인접이 더이상 없을때)
*/
int dR[4] = { -1,1,0,0 };
int dC[4] = { 0,0,-1,1 };	//상하좌우

int BFS(void) {
	int nR, nC, i;
	node curr;
	int time;
	front = rear = 0; //Queue f,r 초기화
	Queue[rear++] = (node){ sR, sC };	//시작정점 입력
	map[sR][sC] = 3;	//방문표시

	while (front != rear) {	//Queue에 데이터가 있으면 (front !=rear)
		curr = Queue[front++];		//정점 DQ
		time = map[curr.r][curr.c] + 1;	//방문표시 용 time (인접끼리 시간은 동일)
		for (i = 0; i < 4; ++i) {	//인접 정점 상하좌우
			nR = curr.r + dR[i];
			nC = curr.c + dC[i];
			if (map[nR][nC] == 1) {	//인접시 (저글링 있으면)
				Queue[rear++] = (node){ nR,nC };	//Q에 넣는다 (EQ)
				map[nR][nC] = time; //방문표시
			}
		}
	}
	return map[curr.r][curr.c];	// (= time - 1 )
}


int main(void) {
	(void)scanf("%d %d", &C, &R);
	inputData();
	//printData();
	(void)scanf("%d %d", &sC, &sR);
	/*
	C에서 함수 인자의 평가 순서는 undefined behavior( 보통 오른쪽 -> 왼쪽)
	BFS()을 먼저 수행해야 rear가 결정되는 경우
	두가지를 동시에 printf의 인자로 넘겨주면 안됌
	printf("%d\n%d\n", BFS(), cnt,rear);
	*/
	printf("%d\n", BFS());
	printf("%d\n", cnt - rear);
	return 0;
}
#endif // 1
