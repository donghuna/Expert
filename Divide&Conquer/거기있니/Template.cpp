/// *** user.cpp ***
extern int countSameNumber(int guess[]);

void consistOf(int N, int K) {

}

int isEntryNumber(int num) {

    return 0;
}

/// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void consistOf(int N, int K);
extern int isEntryNumber(int num);

const int MAX = 100000;
static int N, K, entry[MAX + 5];
static int appear[MAX + 5];
static int tCnt;

int countSameNumber(int guess[]) {
    int cnt = 0;
    for (int i = 0; i < K; ++i) {
        if (guess[i] < 0 || guess[i] > MAX) return MAX;
        cnt += appear[guess[i]];
    }
    return cnt;
}

static void input() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < K; ++i) {
        scanf("%d", entry + i);
        appear[entry[i]] ++;
    }
}

static void run() {
    consistOf(N, K); // 한번 호출
    scanf("%d", &tCnt);
    int num, response;
    for (int i = 0; i < tCnt; ++i) {
        scanf("%d", &num);
        response = isEntryNumber(num);
        printf("%d ", response);
    }
    puts("");
}

int main() {
    freopen("input.txt", "r", stdin);

    input();
    run();
    return 0;
}
