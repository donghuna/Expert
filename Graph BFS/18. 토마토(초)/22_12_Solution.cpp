#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
23_토마토(초)
BFS
빈(-1)=>0, 덜익은(0)=>1, 익은(1)=>2
*/
#include <cstdio>

const int LM = 105;  // limit
int B[LM][LM][LM];
int dh[] = { -1, 1, 0, 0, 0, 0 };
int dr[] = { 0, 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, 0, -1, 1 };

int H, R, C, tomatoCnt;
struct Data {
    int h, r, c, lev;
}que[LM * LM * LM];
int fr, re;  // front, rear

void push(int h, int r, int c, int lev) {
    if (B[h][r][c] == 0) return;  // empty cell
    // 익은 또는 덜익은 토마토가 익는 상황
    tomatoCnt--;
    B[h][r][c] = 0; // 익은 토마토는 박스에서 제거
    que[re++] = { h, r, c, lev };
}

void input() {
    scanf("%d %d %d", &C, &R, &H);
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= R; ++j) {
            for (int k = 1; k <= C; ++k) {
                scanf("%d", B[i][j] + k);
                B[i][j][k] ++;
                if (B[i][j][k])
                    tomatoCnt++;
                if (B[i][j][k] == 2)
                    push(i, j, k, 0);
            }
        }
    }
}

void BFS() {
    while (fr < re) {
        Data t = que[fr++];
        for (int i = 0; i < 6; ++i) {
            push(t.h + dh[i], t.r + dr[i], t.c + dc[i], t.lev + 1);
        }
    }
}

int main() {
#ifdef _WIN32
    freopen("23.txt", "r", stdin);
#endif // _WIN32
    input();
    BFS();
    if (tomatoCnt) puts("-1");
    else printf("%d\n", que[re - 1].lev);
    return 0;
}