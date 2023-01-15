#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
20_구간의 최대값1_ver01
sqrt decomposition : [s, e]
*/
#include <cstdio>

const int LM = 50005;
const int MOD = 256;   // sqrt(50000) = 223.6

int N, Q;
int A[LM];             // 입력데이터 원본
int B[MOD + 5];        // block(구역)별 최대값

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

int query(int s, int e) {
    int ret = -1;
    // 앞쪽 자투리에서 결과값 업데이트하기
    while (s <= e && s % MOD) {
        ret = max(ret, A[s++]);
    }

    // 뒤쪽 자투리에서 결과값 업데이트하기
    while (s <= e && (e + 1) % MOD) {
        ret = max(ret, A[e--]);
    }

    // block(구역)단위로 결과값 업데이트하기
    while (s <= e) {
        ret = max(ret, B[s / MOD]);
        s += MOD;
    }
    return ret;
}
int main() {
#ifdef _WIN32
    freopen("20.txt", "r", stdin);
#endif // _WIN32
    int i, s, e, val;
    scanf("%d %d", &N, &Q);
    for (i = 0; i < N; ++i) {
        scanf("%d", A + i);
        B[i / MOD] = max(B[i / MOD], A[i]);
    }

    for (i = 0; i < Q; ++i) {
        scanf("%d %d", &s, &e);
        printf("%d\n", query(s - 1, e - 1));
    }

    return 0;
}