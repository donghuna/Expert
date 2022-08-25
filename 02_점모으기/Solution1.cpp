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
        tg -= ap[i];                    // 중앙값의 위치를 찾기 위해 개수만큼 빼준다.
        if (tg <= 0) return i;
    }
    return 0;  // impossible
}

int abs(int a) { return a < 0 ? -a : a; }       // abs
int main() {
#ifdef _WIN32
    freopen("02.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d", &N, &M);
    int r, c, i;
    for (i = 0; i < M; ++i) {
        scanf("%d %d", &r, &c);
        rowCnt[r] ++;               // Row, Col 위치값을 저장한다.
        colCnt[c] ++;
    }

    int mr = getMedian(rowCnt, (M + 1) / 2);    // 중앙값이 있는 index를 가져온다.
    int mc = getMedian(colCnt, (M + 1) / 2);

    for (int i = 0; i < LM; ++i) {
        ans += rowCnt[i] * abs(mr - i);     // 이동거리를 계산한다.
        ans += colCnt[i] * abs(mc - i);
    }
    printf("%d\n", ans);
    return 0;
}
