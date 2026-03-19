#if 0
//정올 - 1681 해밀턴 순환회로 https://jungol.co.kr/problem/1681
#define MAX_N (13+1)
#include "___AAA___.h"
#include <limits.h>


int N;
int place_cost[MAX_N][MAX_N];
int visited[MAX_N] = { 0 };
int sum_cost;
int min_cost = INT_MAX;
int move_count;
void input_data() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			(void)scanf("%d", &place_cost[i][j]);
		}
	}
}

void print_data() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			printf("%3d ", place_cost[i][j]);
		}printf("\n");
	}
}
int compare_min_cost(int sum_cost) {
	if (min_cost > sum_cost)
		min_cost = sum_cost;
	return min_cost;
}

void move_place(int L, int depth) {
	if (depth == N) {
		if ((visited[1] == 0) && (place_cost[L][1] != 0)) {
			sum_cost += place_cost[L][1];
			min_cost = compare_min_cost(sum_cost);
			sum_cost -= place_cost[L][1];
			return;
		}
	}
	for (int next = 2; next <= N; ++next) {
		if ((visited[next] == 0) && (place_cost[L][next] != 0)) {
			sum_cost += place_cost[L][next];
			if (sum_cost < min_cost) {
				visited[next] = 1;
				move_place(next, depth + 1);
				visited[next] = 0;
			}
			sum_cost -= place_cost[L][next];
		}
	}
}

int main(void) {
	//(void)freopen("J1681.txt", "r", stdin);
	(void)scanf("%d", &N);
	input_data();
	//print_data();

	move_count = 0;
	sum_cost = 0;
	move_place(1, 1);
	printf("%d", min_cost);

	return 0;
}
#endif // 0
