#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/**
01_마인크래프트_ver03
O(257)
*/
#include <cstdio>

const int LM = 256;
int N, M, B, cnt[LM + 5], sum[LM + 5];
int ansTime, ansHeight;

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif
    scanf("%d %d %d", &N, &M, &B);
    int i, h, an = N * M;
    for (i = 0; i < an; ++i) {
        scanf("%d", &h);
        cnt[h] ++;             // 높이가 i인 셀의 개수 세기
        sum[h] += h;           // 높이가 h인 높이의 합
    }

    for (i = 1; i <= LM; ++i) {
        cnt[i] += cnt[i - 1];    // cnt[i]=높이가 i이하인 셀개수의 총합
        sum[i] += sum[i - 1];    // sum[i]=높이가 i이하인 모든 높이의 총합
    }

    ansTime = sum[LM] * 2;     // h = 0일때 답을 기본 답으로(제거비용은 2초)

    for (h = 1; h <= LM; ++h) {
        int acnt = h * cnt[h - 1] - sum[h - 1];          // 높이 h미만 셀들에게 추가할 블록수
        int bcnt = (sum[LM] - sum[h]) - h * (cnt[LM] - cnt[h]);// 높이 h초과 셀들에서 제거할 블록수
        int remainBlock = B - acnt + bcnt;
        if (remainBlock < 0) break;

        int timeCost = acnt + bcnt * 2; // 추가비용은 1초, 제거비용은 2초
        if (timeCost <= ansTime)
            ansTime = timeCost, ansHeight = h;
    }

    printf("%d %d\n", ansTime, ansHeight);

    return 0;
}
