/*
25_EX최단경로_user_naiveTest02
nonSTL, lookupTable
*/
const int LM = 1 << 20; // 1048576
const int MASK = LM - 1;

int able[5][5] = { {1, 1}, {1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 1} };
int dr[] = { 1, 0, -1, 0 }; // 하, 우, 상, 좌
int dc[] = { 0, 1, 0, -1 };

struct Data {
    int r, c, u, lev;  // 위치(r, c), 값(u), 방문한 셀의 수(lev)
}que[LM];
int fr, re;

char(*map)[40000];

int push(int r, int c, int u, int lev) {
    if (r < 0 || r > 39999 || c < 0 || c > 39999) return 0;
    int v = map[r][c];
    if (able[u][v] == 0) return 0;
    if (r == 39999 && c == 39999) return lev;
    que[re++] = { r, c, v, lev };
    re &= MASK;   // circular queue
    map[r][c] = 4;
    return 0;
}

int test(char map[40000][40000]) {
    ::map = map;
    que[re++] = { 0, 0, map[0][0], 1 };
    map[0][0] = 4;
    while (fr != re) {
        Data t = que[fr++];
        fr &= MASK;  // circular queue

        for (int i = 0; i < 4; ++i) {
            int lev = push(t.r + dr[i], t.c + dc[i], t.u, t.lev + 1);
            if (lev) {
                return lev;
            }
        }
    }
    return 0;
}