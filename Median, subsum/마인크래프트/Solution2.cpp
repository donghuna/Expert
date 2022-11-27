#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
01_마인크래프트_ver02
O(257*257)
*/
#include <cstdio>

const int LM = 250005;
int N, M, B, cnt[LM];
int ansTime = 1 << 30, ansHeight;

int check(int th) {
    int timeCost = 0, inven = B;
    // less than target height
    for (int h = 0; h < th; ++h) {
        inven -= cnt[h] * (th - h);
        timeCost += cnt[h] * (th - h);
    }
    // greater than target height
    for (int h = th + 1; h < 257; ++h) {
        inven += cnt[h] * (h - th);
        timeCost += cnt[h] * (h - th) * 2;
    }

    if (inven >= 0 && timeCost <= ansTime) {
        ansTime = timeCost;
        ansHeight = th;
    }
    return inven < 0;
}

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d %d", &N, &M, &B);
    int an = N * M, h;
    for (int i = 0; i < an; ++i) {
        scanf("%d", &h);
        cnt[h]++;
    }

    for (int h = 0; h < 257; ++h) {
        if (check(h))
            break;
    }
    printf("%d %d\n", ansTime, ansHeight);
    return 0;
}
