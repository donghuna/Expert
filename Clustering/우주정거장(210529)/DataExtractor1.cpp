#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
데이터 좌표 생성에 대한 확률적 분석
    1 : 0.500008
   10 : 0.450000
  100 : 0.045000
 1000 : 0.004500
10000 : 0.000450
65536 : 0.000043
*/
#include <cstdio>
#include <math.h>

using LL = long long;
const LL TOT = 1ll << 32; // 4294967296
const int LM = 65536;
int entry[] = { 1, 10, 100, 1000, 10000, 65536 };
LL cnt[6];

int main() {
    for (int n = 0; n < LM; ++n) {        /// 분자: 0~65535
        for (int d = 1; d <= LM; ++d) {   /// 분모: 1~65536
            double c = (double)n / d;
            if (c < 1) cnt[0] ++;
            else if (c < 10)
                cnt[1] ++;
            else if (c < 100)
                cnt[2] ++;
            else if (c < 1000)
                cnt[3] ++;
            else if (c < 10000)
                cnt[4] ++;
            else
                cnt[5] ++;
        }
    }

    for (int i = 0; i < 6; ++i) {
        printf("%5d : %5.6f\n", entry[i], (double)cnt[i] / TOT);
    }
    return 0;
}
