#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
18_토마토(초)
BFS
Queue, visited
*/
#include <cstdio>

const int LM = 105;
int H, R, C, B[LM][LM][LM];
int cnt;
struct Data {
    int h, r, c, day;
}que[LM * LM * LM];
int fr, re;
int dh[] = {-1, 1, 0, 0, 0, 0};
int dr[] = {0, 0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, 0, -1, 1};

void push(int h, int r, int c, int day) {
    if (B[h][r][c] == 0) return;
    cnt--, B[h][r][c] = 0;
    que[re++] = { h, r, c, day };
}

void input() {
    scanf("%d %d %d", &C, &R, &H);
    // 1:익은, 0:덜익은, -1:빈 을
    // 2:익은, 1:덜익은, 0:빈 으로 바꾸면 경계체크가 쉬워진다.
    int val;
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= R; ++j) {
            for (int k = 1; k <= C; ++k) {
                scanf("%d", &val);
                B[i][j][k] = ++val;
                if (val) cnt++;
                if (val == 2) push(i, j, k, 0);
            }
        }
    }
}


int BFS() {
    while (fr < re) {
        Data&t = que[fr++];
        for (int i = 0; i < 6; ++i) {
            push(t.h + dh[i], t.r + dr[i], t.c + dc[i], t.day + 1);
        }
    }
    if (cnt) return -1;
    return que[re - 1].day;
}


int main() {
#ifdef _WIN32
    freopen("18.txt", "r", stdin);
#endif // _WIN32
    input();
    printf("%d\n", BFS());
    return 0;
}
