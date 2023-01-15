#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
05_구간업데이트2D
prefixSum_2D
*/
#include <cstdio>

using LL = long long;
const int LM = 1005;
int N, Q, A[LM][LM];
LL S[LM][LM];

int main() {
#ifdef _WIN32
	freopen("05.txt", "r", stdin);
#endif // _WIN32
	scanf("%d %d", &N, &Q);
	int sr, sc, er, ec, val;
	for (int i = 0; i < Q; ++i) {
		scanf("%d %d %d %d %d", &sr, &sc, &er, &ec, &val);
		++er, ++ec;
		A[sr][sc] += val, A[er][ec] += val;
		A[sr][ec] -= val, A[er][sc] -= val;
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			S[i][j] = S[i][j - 1] + S[i - 1][j] - S[i - 1][j - 1] + A[i][j];
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			printf("%lld ", S[i][j]);
		}
		puts("");  // printf("\n");
	}
	return 0;
}