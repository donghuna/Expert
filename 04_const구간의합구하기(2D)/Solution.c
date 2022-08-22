#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
04_const구간의합2D
2D prefixSum(subsum)
*/
#include <cstdio>

const int LM = 1004;
using LL = long long;       // long long
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
            S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + A[i][j];    // 위 아래는 더하고, 중복된 값을 빼기위해 좌상단 값은 뺀다. 그리고 현재 value도 더한다.
        }
    }

    scanf("%d", &Q);
    int sr, sc, er, ec;
    while (Q--) {
        scanf("%d%d%d%d", &sr, &sc, &er, &ec);
        sr--, sc--;     // sr, sc 값은 -1 붙여서 계속 사용되기 때문에, 편의상 -1을 해줬다.
        printf("%lld\n", S[er][ec] - S[sr][ec] - S[er][sc] + S[sr][sc]);    // (1,1)에서 구하고자 하는 사각형 오른쪽아래 끝값까지 총합 - 나머지 불필요한부분 제거
    }
    return 0;
}
