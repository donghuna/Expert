#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
01_마인크래프트_ver03
input: O(250000), process: O(257)
*/
#include <cstdio>

const int LM = 256;
int N, M, B, NM;
int cnt[LM + 5], sum[LM + 5];
int ansTime, ansHeight;

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif // _WIN32
    int i, h;
    scanf("%d %d %d", &N, &M, &B);
    NM = N * M;
    for (i = 0; i < NM; ++i) {
        scanf("%d", &h);
        cnt[h] ++;
        sum[h] += h;
    }

    // accumulate
    for (i = 1; i <= LM; ++i) {
        cnt[i] += cnt[i - 1];
        sum[i] += sum[i - 1];
    }

    // 높이를 0으로 하는 답을 기본 답안으로
    ansTime = sum[LM] * 2;

    for (int tgH = 1; tgH <= LM; ++tgH) {
        int smallDiff = tgH * cnt[tgH] - sum[tgH];
        int bigDiff = (sum[LM] - sum[tgH]) - tgH * (cnt[LM] - cnt[tgH]);
        int inven = B - smallDiff + bigDiff;
        if (inven < 0) break;

        int timeCost = smallDiff + bigDiff * 2;
        if (timeCost <= ansTime) {
            ansTime = timeCost;
            ansHeight = tgH;
        }
    }

    printf("%d %d\n", ansTime, ansHeight);

    return 0;
}