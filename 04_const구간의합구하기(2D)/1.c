#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
04_const구간의합2D
2D prefixSum(subsum)
*/
#include <cstdio>

const int LM = 1004;
using LL = long long;
int N, Q, A[LM][LM];
LL S[LM][LM];

int main() {
#ifdef _WIN32
    freopen("04.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            scanf("%d", A[i] + j); // &A[i][j]
            S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + A[i][j];
        }
    }

    scanf("%d", &Q);
    int sr, sc, er, ec;
    while (Q--) {
        scanf("%d%d%d%d", &sr, &sc, &er, &ec);
        sr--, sc--;
        printf("%lld\n", S[er][ec] - S[sr][ec] - S[er][sc] + S[sr][sc]);
    }
    return 0;
}
