/// ***** user.cpp *****
extern double mysqrt(double);
void getStation(double paraCoordi[100000][3], int result[3]) {

}

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
    return ((unsigned short)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

int main(void) {
    int result[3] = { 0, 0, 0 };

    for (register int c = 0; c < 100000; c++) {
        paraCoordi[c][0] = oriCoordi[c][0] = myrandom() / ((double)myrandom() + 1);
        paraCoordi[c][1] = oriCoordi[c][1] = myrandom() / ((double)myrandom() + 1);
        paraCoordi[c][2] = oriCoordi[c][2] = myrandom() / ((double)myrandom() + 1);
    }

    getStation(paraCoordi, result);

    double SCORE = 0.0;

    for (register int c = 0; c < 100000; c++)
    {
        double minVal = 10000000000.0, dist;
        for (register int j = 0; j < 3; j++)
        {
            dist = square(oriCoordi[result[j]][0] - oriCoordi[c][0]);
            dist += square(oriCoordi[result[j]][1] - oriCoordi[c][1]);
            dist += square(oriCoordi[result[j]][2] - oriCoordi[c][2]);

            if (minVal > dist) minVal = dist;
        }

        SCORE += mysqrt(minVal);
    }

    //printf("SCORE: %lf\n", SCORE);
    if (SCORE > 1445000) puts("FAIL");
    else puts("PASS");

    return 0;
}