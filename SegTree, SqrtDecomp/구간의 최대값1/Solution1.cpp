#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
33_구간의 최대값1_ver01
sqrt decomposition
*/
#include <cstdio>

const int INF = 1 << 30;
const int LM = 50005;
const int MOD = 256;
const int MASK = MOD - 1;

int N, Q, A[LM], B[MOD];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

void update(int idx, int newVal) {
    int bn = idx / MOD;                            // 구역 번호 구하기
    int st = bn * MOD, ed = min(N - 1, st + MASK); // bn구역이 담당하는 A[]의 시작번호와 끝 번호
    A[idx] = B[bn] = newVal;                       // 값 업데이트
    while (st <= ed)                               // bn구역의 최대값 구하기
        B[bn] = max(B[bn], A[st++]);
}

int query(int st, int ed) {
    int ret = -INF;
    while (st <= ed && (st & MASK))                  // 앞쪽 자투리에서 최대값 구하기
        ret = max(ret, A[st++]);

    while (st <= ed && ((ed + 1) & MASK))          // 뒤쪽 자투리에서 포함하여 최대값 구하기
        ret = max(ret, A[ed--]);

    for (; st <= ed; st += MOD)                    // 구역단위로 최대값 구하기
        ret = max(ret, B[st / MOD]);
    return ret;
}

int main() {
#ifdef _WIN32
    freopen("33.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif // _WIN32
    scanf("%d %d", &N, &Q);
    int i, val, st, ed;
    for (i = 0; i < N; ++i) {                     // 초기값 입력
        scanf("%d", &val);
        update(i, val);
    }

    for (i = 0; i < Q; ++i) {                      // 쿼리 처리
        scanf("%d %d", &st, &ed);
        printf("%d\n", query(st - 1, ed - 1));     // 0_base로 업데이트 되었으므로...
    }
    return 0;
}