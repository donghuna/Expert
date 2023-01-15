/*
35_우주정거장_문제분석1_확률적분석
*/
#include <cstdio>

using LL = long long;
const int LM = 65536;
const LL total = 1ll << 32;  // 4294967296
int entry[] = { 1, 10, 100, 1000, 10000, 65536 };
LL cnt[6];

int main() {
    for (int num = 0; num < LM; ++num) {
        for (int den = 1; den <= LM; ++den) {
            double d = (double)num / den;
            if (d < entry[0]) cnt[0] ++;
            else if (d < entry[1]) cnt[1] ++;
            else if (d < entry[2]) cnt[2] ++;
            else if (d < entry[3]) cnt[3] ++;
            else if (d < entry[4]) cnt[4] ++;
            else if (d < entry[5]) cnt[5] ++;
        }
    }

    for (int i = 0; i < 6; ++i) {
        printf("%5d 미만 : %f\n", entry[i], (double)cnt[i] / total);
    }
    return 0;
}