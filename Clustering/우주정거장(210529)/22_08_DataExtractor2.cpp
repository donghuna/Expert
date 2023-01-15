#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
seed = 5에서 생성된 100000개의 좌표를 이용하여
원점으로부터 거리 구하여 분석하기
     6 : 75241
    20 : 17121
   100 :  6062
  3000 :  1513
 10000 :    40
113510 :    23
x : 1.214979
y : 1.205571
z : 1.209598
*/

#include <stdio.h>
#include <math.h>

using LL = long long;

int entry[] = { 6, 20, 100, 3000, 10000, 113510 };
int cnt[6], csum;
double xsum, ysum, zsum;

static unsigned short myrandom(void) {
    static unsigned long long seed = 5;
    return ((unsigned short)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

int main(void) {
    for (register int c = 0; c < 100000; c++) {
        double x = myrandom() / ((double)myrandom() + 1);  // (0~65535) / (1~65536)
        double y = myrandom() / ((double)myrandom() + 1);
        double z = myrandom() / ((double)myrandom() + 1);
        double d = sqrt(x * x + y * y + z * z);

        if (d < entry[0]) cnt[0]++;
        else if (d < entry[1]) cnt[1] ++;
        else if (d < entry[2]) cnt[2] ++;
        else if (d < entry[3]) cnt[3] ++;
        else if (d < entry[4]) cnt[4] ++;
        else if (d < entry[5]) cnt[5] ++;

        if (d < entry[0]) {
            xsum += x;
            ysum += y;
            zsum += z;
            csum++;
        }
    }

    for (int i = 0; i < 6; ++i) {
        printf("%6d : %5d\n", entry[i], cnt[i]);
    }

    printf("x : %.6f\n", xsum / csum);
    printf("y : %.6f\n", ysum / csum);
    printf("z : %.6f\n", zsum / csum);
    return 0;
}