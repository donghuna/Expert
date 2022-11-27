//// ***** user.cpp *****
void test(double const house[], double station[], unsigned int alloc[])
{

}


///// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#include <time.h>


void test(double const house[], double station[], unsigned int alloc[]);

static unsigned long long seed = 1;

static unsigned short myrand(void) {
    return ((unsigned short)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}


double house[100000];             // DO NOT MODIFY THIS
double station[5];
unsigned int alloc[100000];


static void build(void) {
    register int loop = 0;

    int alpha = myrand() % 100;
    int beta = myrand() % 100;

    while (loop < 100000)
    {
        int tmp = 0;

        for (int c = 0; c < 3; c++) {
            tmp += (myrand() % 100);
        }

        house[loop++] = (double)((tmp / 3 + alpha) % 100) + (myrand() % 1000000) / 1000000.0;
        house[loop++] = (double)((tmp / 3 + beta) % 100) + (myrand() % 1000000) / 1000000.0;
    }
}


int main()
{
    //    freopen("input.txt", "r", stdin);

    double score = 0, cut = 44700000.0;
    int sd = 5;

    scanf("%d", &sd);

    seed = sd;

    for (int tc = 1; tc <= 100; ++tc) {

        build();

        time_t TIME = clock();
        test(house, station, alloc);
        TIME = clock() - TIME;

        score += (double)TIME / CLOCKS_PER_SEC;
        for (register int c = 0; c < 100000; c++)
        {
            alloc[c] %= 5;
            score += fabs(station[alloc[c]] - house[c]);
        }

        int check[5] = { 0 };

        for (register int c = 0; c < 100000; c++)
        {
            check[alloc[c]]++;
        }

        for (int c = 0; c < 5; c++)
        {
            if (check[c] > 22000)
                score += 100000000;
        }

    }
    scanf("%lf", &cut);

    //    printf("score : %lf\n",score);

    if (score < cut) puts("PASS");
    else puts("FAIL");

    return 0;
}