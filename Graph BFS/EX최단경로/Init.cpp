/// ***** user.cpp *****
int test(char map[40000][40000]) {

}

/// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

extern int test(char map[40000][40000]);

static unsigned long long seed = 13;  // This will be changed
static char map[40000][40000];

static int answer = 80275;            // This will be change by the seed

static void build(void)
{
    for (register int y = 0; y < 40000; y++)
    {
        for (register int x = 0; x < 40000; )
        {
            seed = seed * 25214903917ULL + 11ULL;
            for (register int c = 0; c < 64; c += 2)
            {
                map[y][x++] = (seed >> c) & 0x0000000000000003ULL;
            }
        }
    }
}

int main(void)
{
    double SCORE = 0;

    build();

    time_t tm = clock();
    int userAns = test(map);
    printf("%d %d\n", userAns, answer);
    if (userAns != answer) SCORE += 100000000;
    SCORE += (double)(clock() - tm) / CLOCKS_PER_SEC;

    printf("%lf\n", SCORE);

    return 0;
}