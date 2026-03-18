#if 0
#include "___AAA___.h"

#define MAX_N (15+1)

int N;
int Matrix[MAX_N][MAX_N];
int count = 0;
int up_M[MAX_N + MAX_N];
int down_M[MAX_N + MAX_N];
int col_M[MAX_N];

int check(int R, int C) {
	/*UP üũ*/
	if ((up_M[R + C] == 0) &&
		(down_M[R - C + N] == 0) &&
		(col_M[C]) == 0) {
		return 1;
	}
	return 0;
	/*down üũ*/
}
void Nqueen(int R) {
	if (R > N) {
		count++;
		return;
	}
	for (int C = 1; C <= N; ++C) {
		if (check(R, C)) {
			up_M[R + C] = 1;
			down_M[R - C + N] = 1;
			col_M[C] = 1;
			Nqueen(R + 1);
			up_M[R + C] = 0;
			down_M[R - C + N] = 0;
			col_M[C] = 0;
		}
	}
}

int main(void) {
	(void)scanf("%d", &N);
	Nqueen(1);
	printf("%d", count);
	return 0;
}
#endif // 0