#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
02_점모으기
counting sort
median
*/
#include <cstdio>

const int LM = 10005;
int N, M, ans;
int rowCnt[LM], colCnt[LM];

int getMedian(int*ap, int tg) {
    for (int i = 1; i < LM; ++i) {
        tg -= ap[i];
        if (tg <= 0) return i;
    }
    return 0;  // impossible
}

int abs(int a) { return a < 0 ? -a : a; }
int main() {
#ifdef _WIN32
    freopen("02.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d", &N, &M);
    int r, c, i;
    for (i = 0; i < M; ++i) {
        scanf("%d %d", &r, &c);
        rowCnt[r] ++;
        colCnt[c] ++;
    }

    int mr = getMedian(rowCnt, (M + 1) / 2);
    int mc = getMedian(colCnt, (M + 1) / 2);

    for (int i = 0; i < LM; ++i) {
        ans += rowCnt[i] * abs(mr - i);
        ans += colCnt[i] * abs(mc - i);
    }
    printf("%d\n", ans);
    return 0;
}
