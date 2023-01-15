/*
25_EX최단경로_user_ver01
lookupTable
heuristic : local search
*/
#define rint register int
const int LM = 1 << 20; // 1048576
const int MASK = LM - 1;
const int TH = 1600;

int able[5][5] = { {1, 1}, {1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 1} };
int dr[] = { 1, 0, -1, 0 }; // 하, 우, 상, 좌
int dc[] = { 0, 1, 0, -1 };

struct Data {
    int r, c, u, lev;  // 위치(r, c), 값(u), 방문한 셀의 수(lev)
}que[LM];

int test(char map[40000][40000]) {
    rint fr = 0, re = 0;
    que[re++] = { 0, 0, map[0][0], 1 };
    map[0][0] = 4;
    while (fr != re) {
        Data& t = que[fr++];
        fr &= MASK;  // circular queue

        for (rint i = 0; i < 4; ++i) {
            rint nr = t.r + dr[i], nc = t.c + dc[i];
            if (nr - nc < -TH || nr - nc > TH) continue;     // ***** prunning *****
            if (nr < 0 || nr > 39999 || nc < 0 || nc > 39999) continue;
            rint v = map[nr][nc];
            if (able[t.u][v] == 0) continue;

            if (nr == 39999 && nc == 39999) {
                return t.lev + 1;
            }

            que[re++] = { nr, nc, v, t.lev + 1 };
            re &= MASK;
            map[nr][nc] = 4;
        }
    }
    return 0;
}