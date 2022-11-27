/*
20_EX최단경로_user_naive
FAIL
*/
#include <cstdio>
#include <algorithm>
using namespace std;

#define rint register int
const int LM = 1 << 18; // 262144
const int MASK = LM - 1;

struct Data {
    int r, c, u, lev;
}que[LM];
int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };
int A[5][5] = { {1, 1}, {1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 1} }; // 이동 가능 lookup table

int levCnt[100000];
void output() {
    printf("%d\n", *max_element(levCnt, levCnt + 100000));
}
int test(char map[40000][40000]) {
    rint fr=0, re=0, i;
    que[re++] = { 0, 0, map[0][0], 1 };
    map[0][0] = 4;
    while (fr != re) {
        Data&t = que[fr++];
        levCnt[t.lev]++;
        fr &= MASK;
        for (i = 0; i < 4; ++i) {
            rint nr = t.r + dr[i], nc = t.c + dc[i];
            if (nr < 0 || nr>39999 || nc < 0 || nc>39999) continue;
        
            rint v = map[nr][nc];
            if (A[t.u][v] == 0) continue; // 1. 갈수없는곳, 2.이미 방문한곳

            if (nr == 39999 && nc == 39999) {
                output();
                return t.lev + 1;
            }
            que[re++] = { nr, nc, v, t.lev + 1 };
            map[nr][nc] = 4;
            re &= MASK;
        }
    }
    return 0;
}