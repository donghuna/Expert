/// ***** user.cpp *****
extern int countScore(int guess[]);

void consistOf(int userRet[])
{
}

/// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void consistOf(int userRet[]);
static int SEQ[200];

int countScore(int guess[]) {
    int strike = 0, ball = 0;

    for (register int i = 0; i < 200; i++)
        if (SEQ[i] == guess[i]) strike++;

    for (register int i = 0; i < 200; i++)
        for (register int j = 0; j < 200; j++)
            if (SEQ[i] == guess[j]) ball++;

    return strike * 256 + ball;
}

int main(void)
{
    int SCORE = 0;
    int seed = 5;
    scanf("%d", &seed);
    srand(seed); // number(5) can be changed
    for (int TC = 0; TC < 50; TC++) {
        int chk[256] = { 0 };

        for (register int i = 0; i < 200; i++) {
            int k;
            while (1) {
                k = rand() % 255;
                if (chk[k] == 0) break;
            }
            chk[k] = 1;
            SEQ[i] = k + 1;
        }
        int userRet[200] = { 0 };

        clock_t start = clock();
        consistOf(userRet);
        SCORE += (int)((double)(clock() - start) / CLOCKS_PER_SEC * 1000);
        for (register int i = 0; i < 200; i++)
            if (SEQ[i] != userRet[i]) SCORE += 100000;
    }

    //printf("SCORE: %d\n", SCORE);

    if (SCORE > 2000) puts("FAIL");
    else puts("PASS");

    return 0;
}
