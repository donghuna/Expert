#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
04_const±¸°£ÇÕ(2D)
prefixSum_2D
*/
#include <cstdio>

using LL = long long;
const int LM = 1005;
int N, Q, A[LM][LM];
LL S[LM][LM]; // prefixSum[][]

int main() {
#ifdef _WIN32
    freopen("04.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            scanf("%d", A[i] + j); // &A[i][j];
            S[i][j] = S[i][j - 1] + S[i - 1][j] - S[i - 1][j - 1] + A[i][j];
        }
    }

    int sr, sc, er, ec;
    scanf("%d", &Q);
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d %d", &sr, &sc, &er, &ec);
        LL ans = S[er][ec] - S[sr - 1][ec] - S[er][sc - 1] + S[sr - 1][sc - 1];
        printf("%lld\n", ans);
    }
    return 0;
}
