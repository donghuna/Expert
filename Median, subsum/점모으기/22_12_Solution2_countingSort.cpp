#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
02_점모으기_ver02
median
countingSort : O(N)
*/
#include <cstdio>

const int LM = 10005;
int N, M, ans;
int rowCnt[LM], colCnt[LM];

inline int abs(int a) { return a < 0 ? -a : a; }
void input() {
    scanf("%d %d", &N, &M);
    int i, r, c;
    for (int i = 1; i <= M; ++i) {
        scanf("%d %d", &r, &c);
        rowCnt[r] ++, colCnt[c]++;
    }
}

int getMedian(int* arr, int cnt) {
    for (int i = 1; i <= N; ++i) {
        cnt -= arr[i];
        if (cnt <= 0) return i; // 중앙값을 찾은 경우
    }
    return 0;
}

int main() {
#ifdef _WIN32
    freopen("02.txt", "r", stdin);
#endif // _WIN32
    input();
    int mr = getMedian(rowCnt, (1 + M) / 2);
    int mc = getMedian(colCnt, (1 + M) / 2);

    for (int i = 1; i <= N; ++i) {
        ans += abs(mr - i) * rowCnt[i];
        ans += abs(mc - i) * colCnt[i];
    }

    printf("%d\n", ans);
    return 0;
}