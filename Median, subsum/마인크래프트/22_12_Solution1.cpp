#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
01_마인크래프트_ver01
O(N*M*257) => O(64250000)
*/
#include <cstdio>

const int LM = 250005;
int N, M, NM; // N(세로), M(가로), NM = N * M
int B;        // 인벤 정보
int A[LM];    // 각 셀의 높이 정보
int ansTime = 1 << 30, ansHeight;

int check(int tgH) {
    int timeCost = 0, inven = B;
    for (int i = 0; i < NM; ++i) {
        if (A[i] < tgH) {  // 목표로 하는 높이보다 낮은 셀의 경우
            int diff = tgH - A[i];
            inven -= diff;
            timeCost += diff;
        }
        else {             // 목표로 하는 높이보다 높은 셀의 경우
            int diff = A[i] - tgH;
            inven += diff;
            timeCost += diff * 2;
        }
    }
    if (inven < 0)  // 최종 결과가 음수라면
        return 1;

    if (timeCost <= ansTime) {
        ansTime = timeCost;
        ansHeight = tgH;
    }
    return 0;
}

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d %d", &N, &M, &B);
    NM = N * M;
    for (int i = 0; i < NM; ++i)
        scanf("%d", A + i);  // &A[i]

    for (int h = 0; h < 257; ++h) {
        if (check(h))
            break;
    }

    printf("%d %d\n", ansTime, ansHeight);
    return 0;
}