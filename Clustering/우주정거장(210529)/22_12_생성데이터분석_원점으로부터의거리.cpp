/// ***** min.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>

extern void getStation(double paraCoordi[100000][3], int result[3]);

static double oriCoordi[100000][3];
static double paraCoordi[100000][3];

double mysqrt(double val) {
    return sqrt(val);
}

inline static double square(double val) {
    return val * val;
}

static unsigned short myrandom(void) {
    static unsigned long long seed = 5;
    return ((unsigned short)((seed = seed * 25214903917ULL + 11ULL) >> 16)); // 16, 16, [16], 16 : 0 ~ 65535
}

int D[] = { 6, 50, 500, 3000, 10000, 113510 };
int cnt[7];
double xsum, ysum, zsum;

int main(void) {
    double x, y, z;
    for (register int c = 0; c < 100000; c++) {
        x = myrandom() / ((double)myrandom() + 1);  // (0~65535) / (1~65536)
        y = myrandom() / ((double)myrandom() + 1);
        z = oriCoordi[c][2] = myrandom() / ((double)myrandom() + 1);
        double dist = sqrt(x * x + y * y + z * z);
        if (dist < D[0]) {
            cnt[0]++;
            xsum += x;
            ysum += y;
            zsum += z;
        }
        else if (dist < D[1]) cnt[1]++;
        else if (dist < D[2]) cnt[2]++;
        else if (dist < D[3]) cnt[3]++;
        else if (dist < D[4]) cnt[4]++;
        else if (dist < D[5]) cnt[5]++;
    }

    for (int i = 0; i < 6; ++i)
        printf("거리 %06d 미만 : %d\n", D[i], cnt[i]);

    printf("x1 : %f\n", xsum / cnt[0]);
    printf("y1 : %f\n", ysum / cnt[0]);
    printf("z1 : %f\n", zsum / cnt[0]);
    return 0;
}
