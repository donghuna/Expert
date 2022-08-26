#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
01_마인크래프트_ver01
O(N*M*257) : O(500*500*257)
*/
#include <cstdio>

const int LM = 250005;
int N, M, B, A[LM], an;
int ansTime = 1 << 30, ansHeight;

int check(int targetH) {
    int timeCost = 0, inven = B;
    for (int i = 0; i < an; ++i) {
        if (A[i] < targetH) {
            inven -= targetH - A[i];
            timeCost += targetH - A[i];
        }
        else {
            inven += A[i] - targetH;
            timeCost += (A[i] - targetH) * 2;
        }
    }

    if (inven >= 0 && timeCost <= ansTime) {
        ansTime = timeCost;
        ansHeight = targetH;
    }
    return inven < 0;
}

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d %d", &N, &M, &B);
    an = N * M;
    for (int i = 0; i < an; ++i)
        scanf("%d", A + i); // &A[i]

    for (int h = 0; h < 257; ++h) {
        if (check(h))
            break;
    }
    printf("%d %d\n", ansTime, ansHeight);
    return 0;
}
